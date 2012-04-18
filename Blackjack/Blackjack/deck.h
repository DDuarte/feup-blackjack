#ifndef DECK_H
#define DECK_H

#include "card.h"

#include <stack>
#include <vector>

const unsigned int DEFAULT_NUMBER_OF_DECKS = 1;

class Deck
{
public:
    Deck();
    Deck(unsigned int numberOfDecks);

    Card WithdrawCard();

private:
    std::vector<Card> _cards;

    void InitializeDeck(unsigned int numberOfDecks);
    void Shuffle();
};

#endif // DECK_H