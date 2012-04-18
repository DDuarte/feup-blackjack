#ifndef HAND_H
#define HAND_H

#include "card.h"

#include <vector>

int const AceMaxVal = 11;
int const AceMinVal = 1;
int const BlackjackHand = 21;

class Hand
{
public:
    Hand();
    Hand(std::vector<Card> cards);
    unsigned int GetScore() const { return _score; }
    
    bool IsBusted() { return GetScore() > BlackjackHand; }         // Cannot be const because GetScore()
    bool IsBlackjack() { return GetScore() == BlackjackHand; }     // has to modify Aces score

    void AddCard(Card card);
private:
    std::vector<Card> _cards;
    unsigned int _score;

    void UpdateScore();
};

#endif // HAND_H
