#include "player.h"

Player::Player()
{
    _name = "";
    _balance = 0.0;
    _bet = 0.0;
    _hand = std::vector<Card>();
}

Player::Player(std::string name, double balance)
{
    _name = name;
    _balance = balance;
    _bet = 0.0;
    _hand = std::vector<Card>();
}



