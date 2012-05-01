#include "player.h"
#include "s_game.h"
#include "utilities.h"
#include "gameExceptions.h"
#include "rectButton.h"
#include "deck.h"
#include "hand.h"
#include "fonts.h"
#include "localization.h"

#include <string>
#include <fstream>
#include <exception>
#include <iomanip>
#include <sstream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

std::string Player::_playersFileName = std::string("players.txt");

Player::Player(std::ifstream& file, S_Game* game)
{
    if (!ReadText(file))
        throw InvalidPlayerException();

    _game = game;
    _bet = 0.0;
    _hand = new Hand(Vector2D(0,0)); // Calculate hand position
    // TODO Don't forget to delete this
}

void Player::WriteText(std::ofstream& out) const
{
    out << std::fixed << std::setprecision(2) << _balance << " " << _name;
}

bool Player::ReadText(std::ifstream& file)
{
    file >> _balance;

    getline(file, _name, '\n');

    while (!_name.empty() && _name[0] == ' ')
        _name.erase(_name.begin());

    return !_name.empty();
}

void Player::PlaceBet(double bet)
{
    if (bet <= 0 || bet > _balance)
        throw InvalidBetException("Invalid bet exception at Player::Set(double bet)!");

    _bet = bet;
    _balance -= bet;

    _game->PlayerBet(this, bet);
}

bool Player::Hit(RectButton* btn)
{
    Card* tempCard = _game->GetDeck()->WithdrawCard();

    if (tempCard != NULL)
    {
        _hand->AddCard(tempCard);
        _game->PlayerHit(this);
    }
    else
        _game->HandleOutOfCards();
    return true;
}

bool Player::Stand(RectButton* btn)
{
    _game->PlayerStand(this);
    return true;
}

bool Player::Double(RectButton* btn)
{
    Card* tempCard = _game->GetDeck()->WithdrawCard();

    if (tempCard != NULL)
    {
        _hand->AddCard(tempCard);
        _balance -= _bet;
        _bet *= 2;
        _game->PlayerDouble(this);
    }
    else
        _game->HandleOutOfCards();

    // ...
    return true;
}

void Player::Lose()
{
    _bet = 0;
    _hand->Clear(); // This must be taken because if not when a player busts he doesn't see the last card
}

void Player::ResetPlayer()
{
    _bet = 0;
    ClearHand();
}

void Player::Draw()
{
    // must draw hand, player name and total money

    const char* name = _name.c_str();

    std::stringstream ss;
    ss << _balance << ' ' << "€"; // euro symbol

    // must convert to USTR because we got the euro special symbol
    // P.S Encodings suck.
    ALLEGRO_USTR* balance = al_ustr_new(ss.str().c_str());

    al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 255, 255),
        _drawPosition.X + 10, _drawPosition.Y + 10 + 105, 0, name);
    al_draw_ustr(Fonts::GetFont(20), al_map_rgb(255, 255, 255),
        _drawPosition.X + 10, _drawPosition.Y - 10 + 105, 0, balance);

    _hand->SetPosition(_drawPosition); // should only be called once, NOT every draw
    _hand->Draw();
}
