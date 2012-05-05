#ifndef DECK_H
#define DECK_H

#include "utilities.h"
#include "card.h"

#include <vector>

const uint DEFAULT_NUMBER_OF_DECKS = 1;
const uint NUMBER_OF_CARDS = 52;
const uint NUMBER_OF_SUITS = 4;
const uint NUMBER_OF_CARDS_PER_SUIT = NUMBER_OF_CARDS/NUMBER_OF_SUITS;
const Vector2D DECK_POSITION = Vector2D(550, 80);

struct ALLEGRO_SAMPLE;

class Deck
{
public:
    Deck(uint numberOfDecks = DEFAULT_NUMBER_OF_DECKS);

    Card* WithdrawCard();

    void ReInitializeDeck(uint numberOfDecks = DEFAULT_NUMBER_OF_DECKS) { InitializeDeck(numberOfDecks); }

    void Draw(bool cardBack = true);

private:
    std::vector<Card> _cards;

    void InitializeDeck(uint numberOfDecks);
    void Shuffle();

    ALLEGRO_SAMPLE* _shuffleSound;
};

#endif // DECK_H
