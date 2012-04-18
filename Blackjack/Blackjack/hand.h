#ifndef HAND_H
#define HAND_H

#include "card.h"

#include <vector>

class Hand
{
public:
    Hand();
    Hand(std::vector<Card> cards);
    unsigned int GetScore();
    
    bool IsBusted() { return GetScore() > 21; }         // Cannot be const because GetScore()
    bool IsBlackjack() { return GetScore() == 21; }     // has to modify Aces score

    void AddCard(Card card);
private:
    std::vector<Card> _cards;
    
};
#endif // HAND_H