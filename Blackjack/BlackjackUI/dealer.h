#ifndef DEALER_H
#define DEALER_H

#include "hand.h"
#include "s_game.h"

class Card;
class S_Game;

class Dealer
{
public:
    Dealer(S_Game* game);

    const Hand* GetHand() const { return &_hand; }

    bool IsBusted() { return _hand.IsBusted(); }
    bool IsBlackjack() { return _hand.IsBlackjack(); }

    void Hit();
    void Stand();
    
    void AddNewCard(Card* card) { _hand.AddCard(card); }
    void ClearHand() { _hand.Clear(); }

private:
    Hand _hand;
    S_Game* _game;

    //Statistics
    /*double _totalBets;*/ //Only used to final statistics
};

#endif // DEALER_H