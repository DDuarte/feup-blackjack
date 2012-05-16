#ifndef DEALER_H
#define DEALER_H

#include "hand.h"
#include "s_game.h"
#include "utilities.h"

class Card;
class S_Game;

const Vector2D DEALER_POSITION = Vector2D(265,63);

class Dealer
{
public:
    Dealer(S_Game* game);

    bool IsBusted() { return _hand.IsBusted(); }
    bool IsBlackjack() { return _hand.IsBlackjack(); }

    bool Hit();

    void NewCard(Card* card);
    void ClearHand() { _hand.Clear(); }
    uint GetScore() const { return _hand.GetScore(); }

    void NoShowSecondCard() { _hand.NoShowSecondCard(); }
    void ShowSecondCard() { _hand.ShowSecondCard(); }
    void Draw();

private:
    Hand _hand;
    S_Game* _game;
};

#endif // DEALER_H
