#ifndef HAND_H
#define HAND_H

#include "utilities.h"

#include <vector>

int const ACE_MAX_VAL = 11;
int const ACE_MIN_VAL = 1;
int const BLACKJACK_HAND = 21;

class Card;

class Hand
{
public:
    Hand();
    Hand(Vector2D position, bool dealerHand = false);

    uint GetScore() const { return _score; }
    uint GetNumberOfCards()const { return _cards.size(); }

    bool IsBusted() const { return GetScore() > BLACKJACK_HAND; }
    bool IsBlackjack() const { return GetScore() == BLACKJACK_HAND && _cards.size() == 2; }

    void AddCard(Card* card);
    void Clear();

    void Draw();
    void ShowSecondCard() { _drawSecondCardBack = false; }
    void NoShowSecondCard() { _drawSecondCardBack = true; }

    void SetPosition(Vector2D position) { _position = position; }
    bool IsPositionSet() { return _position.X != 0 && _position.Y != 0; }

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
