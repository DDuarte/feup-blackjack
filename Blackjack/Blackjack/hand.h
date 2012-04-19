#ifndef HAND_H
#define HAND_H

#include "card.h"

#include <vector>
#include <algorithm>

int const ACE_MAX_VAL = 11;
int const ACE_MIN_VAL = 1;
int const BLACKJACK_HAND = 21;

class Hand
{
public:
    Hand();
    ~Hand();

    unsigned int GetScore() const { return _score; }
    
    bool IsBusted() const { return GetScore() > BLACKJACK_HAND; }
    bool IsBlackjack() const { return GetScore() == BLACKJACK_HAND; }

    void AddCard(Card* card);
    void RemoveCard(const Card* card);
    void Clear();

private:
    std::vector<Card*> _cards;
    unsigned int _score;

    void UpdateScore();
};

#endif // HAND_H
