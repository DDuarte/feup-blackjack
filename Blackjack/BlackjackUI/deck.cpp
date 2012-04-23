#include "utilities.h"
#include "deck.h"
#include "card.h"
#include "blackjack.h"

#include <ctime>
#include <stack>
#include <vector>

Deck::Deck(uint numberOfDecks /*= DEFAULT_NUMBER_OF_DECKS*/)
{
    InitializeDeck(numberOfDecks);
}

void Deck::InitializeDeck(uint numberOfDecks)
{
    _cards = std::vector<Card>();

    _cards.reserve(NUMBER_OF_CARDS*numberOfDecks);

    CardSuit types[] = { CARD_SUIT_CLUBS, CARD_SUIT_SPADES,
                        CARD_SUIT_HEARTS, CARD_SUIT_DIAMONDS };

    for (uint i = 0; i < NUMBER_OF_SUITS*numberOfDecks; ++i)
    {
        int suit = i % NUMBER_OF_SUITS;
        _cards.push_back(Card(types[suit], CARD_RANK_TWO, 2));
        _cards.push_back(Card(types[suit], CARD_RANK_THREE, 3));
        _cards.push_back(Card(types[suit], CARD_RANK_FOUR, 4));
        _cards.push_back(Card(types[suit], CARD_RANK_FIVE, 5));
        _cards.push_back(Card(types[suit], CARD_RANK_SIX, 6));
        _cards.push_back(Card(types[suit], CARD_RANK_SEVEN, 7));
        _cards.push_back(Card(types[suit], CARD_RANK_EIGHT, 8));
        _cards.push_back(Card(types[suit], CARD_RANK_NINE, 9));
        _cards.push_back(Card(types[suit], CARD_RANK_TEN, 10));
        _cards.push_back(Card(types[suit], CARD_RANK_JACK, 10));
        _cards.push_back(Card(types[suit], CARD_RANK_QUEEN, 10));
        _cards.push_back(Card(types[suit], CARD_RANK_KING, 10));
        _cards.push_back(Card(types[suit], CARD_RANK_ACE, 0)); // 11 or 1
    }

    Shuffle();
}

Card* Deck::WithdrawCard()
{
    if (_cards.size() == 0)
        return NULL;

    Card* tempCard = &_cards.back();
    _cards.pop_back();
    return tempCard;
}

void Deck::Shuffle()
{
    size_t size = _cards.size();

    for (size_t i = 0; i < _cards.size(); ++i)
    {
        int r1;
        do r1 = rand() % size;
        while (r1 == i);

        std::swap(_cards[r1], _cards[i]);
    }
}

void Deck::Draw(float dx, float dy, bool cardBack/* = false*/)
{
    for (uint i = 0; i < _cards.size(); i+=2) // Drawing each card makes a very
    {                                         // big deck on the screen
        dx += 1;
        dy += 1;

        if (cardBack)
            _cards[i].DrawBack(dx, dy);
        else
            _cards[i].Draw(dx, dy);
    }
}