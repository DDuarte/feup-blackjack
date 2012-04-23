#ifndef DECK_H
#define DECK_H

#include "utilities.h"
#include "card.h"

#include <stack>
#include <vector>

const uint DEFAULT_NUMBER_OF_DECKS = 1;
const uint NUMBER_OF_CARDS = 52;
const uint NUMBER_OF_SUITS = 4;
const uint NUMBER_OF_CARDS_PER_SUIT = NUMBER_OF_CARDS/NUMBER_OF_SUITS;

class Deck
{
public:
    Deck(uint numberOfDecks = DEFAULT_NUMBER_OF_DECKS);

    Card* WithdrawCard();

    uint GetGameCardsNumber() { return _cards.size(); }

    void Draw(float dx, float dy, bool cardBack = false);

private:
    std::vector<Card> _cards;

    void InitializeDeck(uint numberOfDecks);
    void Shuffle();
};

#endif // DECK_H
