#include "player.h"
#include "s_game.h"
#include "utilities.h"
#include "gameExceptions.h"
#include "rectButton.h"

#include <string>
#include <fstream>
#include <exception>
#include <fstream>
#include <iomanip>

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
    out << std::fixed << std::setprecision(2) << _balance << " " << _name; // << _bet; It isn't needed because we don't want to save Player bet;
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

bool Player::Hit()
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

bool Player::Stand()
{
    _game->PlayerStand(this);
    return true;
}

bool Player::Double()
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
    _hand->Clear();
}

void Player::ResetPlayer()
{
    _bet = 0;
    ClearHand();
}



