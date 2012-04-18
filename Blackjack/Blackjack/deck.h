#ifndef DECK_H
#define DECK_H

#include "card.h"

#include <vector>

class Deck
{
public:
    Deck();

    void DrawCard();

private:
    std::vector<Card> _cards;

    void Shuffle();
};

#endif // DECK_H