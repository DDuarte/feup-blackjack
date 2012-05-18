/*!
 * \file deck.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

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

/*!
 * \class Deck
 *
 * \brief Represents a deck of cards
 *
 */
class Deck
{
public:
    //! Constructor
    Deck(uint numberOfDecks = DEFAULT_NUMBER_OF_DECKS);

    //! Removes and returns a card from the top of the deck
    Card* WithdrawCard();

    //! Creates a new (shuffled) deck (52 cards)
    void ReInitializeDeck(uint numberOfDecks = DEFAULT_NUMBER_OF_DECKS) { InitializeDeck(numberOfDecks); }

    //! Draws the deck in the playing field
    void Draw(bool cardBack = true);

private:
    std::vector<Card> _cards;

    void InitializeDeck(uint numberOfDecks);
    void Shuffle();
};

#endif // DECK_H
