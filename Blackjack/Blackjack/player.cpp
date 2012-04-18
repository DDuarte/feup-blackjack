#include "player.h"
#include "utilities.h"

#include <string>
#include <fstream>
#include <exception>
#include <fstream>

std::string Player::_playersFileName = std::string("players.data");

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

Player::Player(std::ifstream& file)
{
    if (!ReadBinary(file))
        ; //throw invalid file exception
}


void Player::WriteBinary( std::ofstream& out )
{
    out << _name << '\0' << _balance; // << _bet; It isn't needed because we don't want to save Player bet;
}

bool Player::ReadBinary( std::ifstream& file )
{

        char phrase[200];
        file.getline(phrase, 200, '\0');

        _name = std::string(phrase);

        if(*phrase == '\0')
            return false;

    file >> _balance;
    
    return true;
}

void Player::SetPlayersFileName(std::string playersFileName)
{
    if (!Utilities::FileExists(playersFileName.c_str()))
    {
        std::fstream out (playersFileName.c_str(), std::ios::out | std::ios::binary);
        if (!out.is_open())
            ;//throw exception
        out.close();
    }

    _playersFileName = playersFileName;
}
