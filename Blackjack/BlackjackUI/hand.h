/*!
 * \file hand.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#ifndef HAND_H
#define HAND_H

#include "utilities.h"

#include <vector>

int const ACE_MAX_VAL = 11;
int const ACE_MIN_VAL = 1;
int const BLACKJACK_HAND = 21;

class Card;

/*!
 * \class Hand
 *
 * \brief Represents a hand of cards
 * Both used by players and dealer
 *
 */
class Hand
{
public:
    //! Constructor
    Hand();
    //! Destructor
    Hand(Vector2D position, bool dealerHand = false);

    //! Scores
    uint GetScore() const { return _score; }
    //! Number of cards in hand
    uint GetNumberOfCards() const { return _cards.size(); }

    //! True if score is higher than 21
    bool IsBusted() const { return GetScore() > BLACKJACK_HAND; }
    //! True if score is 21 (with 2 cards)
    bool IsBlackjack() const { return GetScore() == BLACKJACK_HAND && _cards.size() == 2; }

    //! Adds a new card to the hand
    void AddCard(Card* card);
    //! Removes all cards from the hand
    void Clear();

    //! Draws the hand to the screen
    void Draw();
    //! Show second card
    void ShowSecondCard() { _drawSecondCardBack = false; }
    //! Do not show second card
    void NoShowSecondCard() { _drawSecondCardBack = true; }

    //! Changes draw position
    void SetPosition(Vector2D position) { _position = position; }
    //! True if position is set
    bool IsPositionSet() const { return _position.X != 0 && _position.Y != 0; }

private:
    std::vector<Card*> _cards;
    uint _score;

    bool _dealerHand;
    bool _drawSecondCardBack;
    int _cardJustAdded;

    Vector2D _position;

    void UpdateScore();
};

#endif // HAND_H
