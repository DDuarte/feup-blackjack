#include "utilities.h"
#include "deck.h"
#include "card.h"

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

    CardSuit types[] = { Clubs, Spades, Hearts, Diamonds };

    for (uint i = 0; i < NUMBER_OF_SUITS*numberOfDecks; ++i)
    {
        int suit = i % NUMBER_OF_SUITS;
        _cards.push_back(Card(types[suit], Two, 2));
        _cards.push_back(Card(types[suit], Three, 3));
        _cards.push_back(Card(types[suit], Four, 4));
        _cards.push_back(Card(types[suit], Five, 5));
        _cards.push_back(Card(types[suit], Six, 6));
        _cards.push_back(Card(types[suit], Seven, 7));
        _cards.push_back(Card(types[suit], Eight, 8));
        _cards.push_back(Card(types[suit], Nine, 9));
        _cards.push_back(Card(types[suit], Ten, 10));
        _cards.push_back(Card(types[suit], Jack, 10));
        _cards.push_back(Card(types[suit], Queen, 10));
        _cards.push_back(Card(types[suit], King, 10));
        _cards.push_back(Card(types[suit], Ace, 0)); // 11 or 1
    }

    Shuffle();

    for (uint i = 0; i < _cards.size(); ++i)
        _gameCards.push(&_cards[i]);
}

Card* Deck::WithdrawCard()
{
    if (_gameCards.size() == 0)
        return NULL;

    Card* tempCard = _gameCards.top();
    _gameCards.pop();
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
        
        Utilities::Swap(_cards[r1], _cards[i]);
    }
}
