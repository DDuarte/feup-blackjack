#ifndef PLAYER_H
#define PLAYER_H

#include "gameExceptions.h"
#include "utilities.h"
#include "hand.h"

#include <string>
#include <vector>
#include <fstream>

class Card;
class BlackJack;

// Only BlackJack class will create objects of this type
// _game should be used to tell "BlackJack" that this player did a bet/stand/etc

class Player
{
public:
    Player(std::string name, double balance, BlackJack* game);
    Player(std::ifstream& file, BlackJack* game);
    // ~Player();

    std::string GetName() const { return _name; }
    double GetBalance() const { return _balance; }
    double GetBet() const { return _bet; }
    const Hand* GetHand() const { return &_hand; }
    static std::string GetPlayersFileName() { return _playersFileName; }

    void SetName(std::string name) { if (name.size() > 0) _name = name; }
    // void SetBalance(double balance) { _balance = balance; }
    static void SetPlayersFileName(std::string playersFileName);

    bool IsBusted() { return _hand.IsBusted(); }
    bool IsBlackjack() { return _hand.IsBlackjack(); }

    bool ReadBinary(std::ifstream& in);
    void WriteBinary(std::ofstream& out);

    // In-game player actions
    void PlaceBet(double bet);
    void Stand() { }
    void Hit() { }
    void Double() { }

    void NewHand(Card* card1, Card* card2) { _hand.Clear(); _hand.AddCard(card1); _hand.AddCard(card2); }

private:
    std::string _name;
    double _balance;
    double _bet;
    
    static std::string _playersFileName;

    Hand _hand;
    BlackJack* _game;
};

#endif // PLAYER_H
