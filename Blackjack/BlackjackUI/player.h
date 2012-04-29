#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include "rectButton.h"

#include <string>
#include <vector>
#include <fstream>

class Card;
class S_Game;

// Only s_game class will create objects of this type
// _game should be used to tell "BlackJack" that this player did a bet/stand/etc

class Player
{
public:
    Player(std::ifstream& file, S_Game* game);

    std::string GetName() const { return _name; }
    double GetBalance() const { return _balance; }
    double GetBet() const { return _bet; }
    Hand* GetHand() const { return _hand; }
    static std::string GetPlayersFileName() { return _playersFileName; }

    bool IsBusted() { return _hand->IsBusted(); }
    bool IsBlackjack() { return _hand->IsBlackjack(); }

    void WriteText(std::ofstream& out) const;

    // In-game player actions
    void PlaceBet(double bet);
    bool Stand(RectButton* btn);
    bool Hit(RectButton* btn);
    bool Double(RectButton* btn);
    void Lose();
    void ResetPlayer();

    void NewCard(Card* card) { _hand->AddCard(card); }
    void ClearHand() { _hand->Clear(); }

private:
    bool ReadText(std::ifstream& in);

    std::string _name;
    double _balance;
    double _bet;

    static std::string _playersFileName;

    Hand* _hand;
    S_Game* _game;
};

#endif // PLAYER_H
