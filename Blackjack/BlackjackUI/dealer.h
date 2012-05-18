/*!
 * \file dealer.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#ifndef DEALER_H
#define DEALER_H

#include "hand.h"
#include "s_game.h"
#include "utilities.h"

class Card;
class S_Game;

const Vector2D DEALER_POSITION = Vector2D(265,63);

/*!
 * \class Dealer
 *
 * \brief Represents the dealer of the blackjack game
 *
 */
class Dealer
{
public:
    //! Constructor
    Dealer(S_Game* game);

    //! Returns true if dealer got more than 21 points
    bool IsBusted() { return _hand.IsBusted(); }
    //! Returns true if dealer got 21 points (with only 2 cards)
    bool IsBlackjack() { return _hand.IsBlackjack(); }

    //! Dealer hit
    bool Hit();

    //! Adds a new card to dealer's hand
    void NewCard(Card* card);
    //! Removes all cards from dealer's hand
    void ClearHand() { _hand.Clear(); }
    //! Returns the score of dealer's hand
    uint GetScore() const { return _hand.GetScore(); }

    //! Do not show second card
    void NoShowSecondCard() { _hand.NoShowSecondCard(); }
    //! Show second card
    void ShowSecondCard() { _hand.ShowSecondCard(); }
    //! Draw dealer name and hand to the playing field
    void Draw();

private:
    Hand _hand;
    S_Game* _game;
};

#endif // DEALER_H
