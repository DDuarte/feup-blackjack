#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "hand.h"
#include "gameExceptions.h"
#include "utilities.h"

#include <string>
#include <vector>
#include <fstream>

class Card;

class Player
{
public:
    Player(std::string name, double balance);
    Player(std::ifstream& file);

    std::string GetName() const { return _name; }
    double GetBalance() const { return _balance; }
    double GetBet() const { return _bet; }
    Hand GetHand() const { return _hand; }
    static std::string GetPlayersFileName() { return _playersFileName; }

    void SetName(std::string name) { if (name.size() > 0) _name = name; }
    // void SetBalance(double balance) { _balance = balance; }
    static void SetPlayersFileName(std::string playersFileName);

    bool IsBusted() { return _hand.IsBusted(); }         
    bool IsBlackjack() { return _hand.IsBlackjack(); } 

    bool ReadBinary(std::ifstream& in);
    void WriteBinary(std::ofstream& out);

    // In-game actions
    void PlaceBet(double bet);
    void Stand() { }
    void Hit() { }
    void Double() { }

private:
    std::string _name;
    double _balance;
    double _bet;
    Hand _hand;
    static std::string _playersFileName;
};

#endif // PLAYER_H
