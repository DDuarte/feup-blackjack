#include "player.h"
#include "s_game.h"
#include "utilities.h"
#include "game_exceptions.h"
#include "rect_button.h"
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
    _hand = new Hand(Vector2D(0,0));
    // TODO Don't forget to delete this

    _doubleBet = false;
    _index = -1;
}

void Player::Save(std::ofstream& out) const
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

void Player::PlaceBet()
{
    double bet = S_Game::GetBet();

    if (bet <= 0 || bet > _balance)
        throw InvalidBetException("Invalid bet exception at Player::PlaceBet(double bet)!");

    _balance -= bet;

    _game->PlayerBet(this);
}

bool Player::Hit(RectButton* btn)
{
    if (Card* card = _game->GetDeck()->WithdrawCard())
    {
        _hand->AddCard(card);
        _game->PlayerHit(this, card);
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
    if (Card* card = _game->GetDeck()->WithdrawCard())
    {
        _hand->AddCard(card);
        _balance -= S_Game::GetBet();
        _doubleBet = true;
        _game->PlayerDouble(this, card);
    }
    else
        _game->HandleOutOfCards();

    // ...
    return true;
}

void Player::ResetPlayer()
{
    _doubleBet = false;
    ClearHand();
}

void Player::Draw(bool activePlayer /*= false*/)
{
    if (_index == -1)
        return;

    const char* name = _name.c_str();

    std::stringstream ss;
    ss << _balance << ' ' << "€"; // euro symbol

    // must convert to USTR because we got the euro special symbol
    // P.S Encodings suck.
    ALLEGRO_USTR* balance = al_ustr_new(ss.str().c_str());

    if (activePlayer) al_draw_filled_rectangle(
        PLAYER_POSITIONS[_index].X + 10, 
        PLAYER_POSITIONS[_index].Y + 10 + 105, 
        PLAYER_POSITIONS[_index].X + Fonts::GetFont(20)->vtable->text_length(Fonts::GetFont(20), al_ustr_new(name)) + 10,
        PLAYER_POSITIONS[_index].Y + 10 + 105 + Fonts::GetFont(20)->height, al_map_rgb(120, 120, 255));
    al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 255, 255),
        PLAYER_POSITIONS[_index].X + 10, PLAYER_POSITIONS[_index].Y + 10 + 105, 0, name);
    al_draw_ustr(Fonts::GetFont(20), al_map_rgb(255, 255, 255),
        PLAYER_POSITIONS[_index].X + 10, PLAYER_POSITIONS[_index].Y - 10 + 105, 0, balance);

    _hand->Draw();

    al_draw_scaled_bitmap(_game->GetChip(), 0, 0, al_get_bitmap_width(_game->GetChip()), al_get_bitmap_height(_game->GetChip()), PLAYER_POSITIONS[_index].X - 30 - 5, PLAYER_POSITIONS[_index].Y + 5, 30, 30, 0);
    if (_doubleBet)
        al_draw_scaled_bitmap(_game->GetChip(), 0, 0, al_get_bitmap_width(_game->GetChip()), al_get_bitmap_height(_game->GetChip()), PLAYER_POSITIONS[_index].X - 30 - 5, PLAYER_POSITIONS[_index].Y + 5 + 30 + 5, 30, 30, 0);
}

void Player::EnterGame(int index)
{
    ResetPlayer();
    _hand->SetPosition(PLAYER_POSITIONS[index]);
    _index = index;
}
