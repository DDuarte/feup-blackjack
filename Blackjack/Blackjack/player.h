#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
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
    std::vector<Card> GetHand() const { return _hand; };

    void SetName(std::string name) { if (name.size() > 0) _name = name; };
    void SetBalance(double balance) { _balance = balance; };

    void PlaceBet(double bet) { _bet = bet; /* ... */ };

private:
    std::string _name;
    double _balance;
    double _bet;
    std::vector<Card> _hand;
};

#endif // PLAYER_H
