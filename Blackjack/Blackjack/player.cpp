#include "player.h"
#include "blackjack.h"
#include "utilities.h"

#include <string>
#include <fstream>
#include <exception>
#include <fstream>
#include <iomanip>

std::string Player::_playersFileName = std::string("players.txt");

Player::Player(std::ifstream& file, BlackJack* game)
{
    if (!ReadText(file))
        throw InvalidPlayerException();

    _game = game;
    _bet = 0.0;
    _hand = Hand();
}

void Player::WriteText(std::ofstream& out) const
{
    out << std::fixed << std::setprecision(2) << _balance << " " << _name; // << _bet; It isn't needed because we don't want to save Player bet;
}

bool Player::ReadText(std::ifstream& file)
{
    file >> _balance;

    getline(file, _name, '\n');

    while ( !_name.empty() && _name.at(0) == ' ')
    {
        _name.erase(_name.begin());
    }

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

void Player::Hit()
{
    Card* tempCard = _game->GetDeck()->WithdrawCard();

    if (tempCard != NULL)
    {
        _hand.AddCard(tempCard);
        _game->PlayerHit(this);
    }
    else
        _game->HandleOutOfCards();
}

void Player::Stand()
{
    _game->PlayerStand(this);
}

void Player::Double()
{
    Card* tempCard = _game->GetDeck()->WithdrawCard();

    if (tempCard != NULL)
    {
        _hand.AddCard(tempCard);
        _bet *= 2;


        _game->PlayerDouble(this);
    }
    else
        _game->HandleOutOfCards();

    
}

