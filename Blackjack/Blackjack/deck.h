#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

class Deck
{
public:
    void DrawCard();

private:
    std::vector<Card> _cards;
};

#endif // DECK_H