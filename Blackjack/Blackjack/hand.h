#ifndef HAND_H
#define HAND_H

#include "card.h"

#include <vector>

int const ACE_MAX_VAL = 11;
int const ACE_MIN_VAL = 1;
int const BLACKJACK_HAND = 21;

class Hand
{
public:
    Hand();
    Hand(std::vector<Card> cards);
    unsigned int GetScore() const { return _score; }
    
    bool IsBusted() { return GetScore() > BLACKJACK_HAND; }         // Cannot be const because GetScore()
    bool IsBlackjack() { return GetScore() == BLACKJACK_HAND; }     // has to modify Aces score

    void AddCard(Card card);
private:
    std::vector<Card> _cards;
    unsigned int _score;

    void UpdateScore();
};

#endif // HAND_H
