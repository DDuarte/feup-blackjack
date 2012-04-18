#ifndef DECK_H
#define DECK_H

#include "card.h"

#include <stack>
#include <vector>

const unsigned int DEFAULT_NUMBER_OF_DECKS = 1;
const unsigned int NUMBER_OF_CARDS = 52;
const unsigned int NUMBER_OF_SUITS = 4;
const unsigned int NUMBER_OF_CARDS_PER_SUIT = NUMBER_OF_CARDS/NUMBER_OF_SUITS;

class Deck
{
public:
    Deck(unsigned int numberOfDecks = DEFAULT_NUMBER_OF_DECKS);

    Card WithdrawCard();

private:
    std::vector<Card> _cards;

    void InitializeDeck(unsigned int numberOfDecks);
    void Shuffle();
};

#endif // DECK_H