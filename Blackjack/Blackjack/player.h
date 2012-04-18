#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "hand.h"
#include "gameExceptions.h"

#include <string>
#include <vector>

class Card;

class Player
{
public:
    Player();
    Player(std::string name, double balance);

    std::string GetName() const { return _name; };
    double GetBalance() const { return _balance; };
    double GetBet() const { return _bet; };
    Hand GetHand() const { return _hand; };

    bool IsBusted() { return GetHand().IsBusted(); }         
    bool IsBlackjack() { return GetHand().IsBlackjack(); } 

    void SetName(std::string name) { if (name.size() > 0) _name = name; };
    void SetBalance(double balance) { _balance = balance; };

    void SetBet(double bet) { (bet > 0 ? _bet = bet : throw InvalidBetException("Invalid bet exception at Player::IncreaseBet(double bet)!")); };
    void IncreaseBet(double bet) { (bet > 0 ? _bet += bet : throw InvalidBetException("Invalid bet exception at Player::IncreaseBet(double bet)!")); };

    void WriteBinary(std::ofstream& out);

private:
    std::string _name;
    double _balance;
    double _bet;
    Hand _hand;
};

#endif // PLAYER_H
