#include "player.h"
#include "utilities.h"
#include <string>
#include <fstream>

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

void Player::WriteBinary( std::ofstream& out )
{
    out << _name << '/0' << _balance << _bet;
}



