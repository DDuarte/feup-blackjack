#include "utilities.h"
#include "deck.h"
#include "card.h"

#include <ctime>
#include <stack>
#include <vector>

Deck::Deck(unsigned int numberOfDecks /*= DEFAULT_NUMBER_OF_DECKS*/)
{
    InitializeDeck(numberOfDecks);
}

void Deck::InitializeDeck(unsigned int numberOfDecks)
{
    _cards = std::vector<Card>();

    _cards.reserve(NUMBER_OF_CARDS*numberOfDecks);

    CardSuit types[] = { Clubs, Spades, Hearts, Diamonds };

    for (unsigned int i = 0; i < NUMBER_OF_SUITS*numberOfDecks; ++i)
    {
        _cards.push_back(Card(types[i%NUMBER_OF_SUITS], Two, 2));
        _cards.push_back(Card(types[i%NUMBER_OF_SUITS], Three, 3));
        _cards.push_back(Card(types[i%NUMBER_OF_SUITS], Four, 4));
        _cards.push_back(Card(types[i%NUMBER_OF_SUITS], Five, 5));
        _cards.push_back(Card(types[i%NUMBER_OF_SUITS], Six, 6));
        _cards.push_back(Card(types[i%NUMBER_OF_SUITS], Seven, 7));
        _cards.push_back(Card(types[i%NUMBER_OF_SUITS], Eight, 8));
        _cards.push_back(Card(types[i%NUMBER_OF_SUITS], Nine, 9));
        _cards.push_back(Card(types[i%NUMBER_OF_SUITS], Ten, 10));
        _cards.push_back(Card(types[i%NUMBER_OF_SUITS], Jack, 10));
        _cards.push_back(Card(types[i%NUMBER_OF_SUITS], Queen, 10));
        _cards.push_back(Card(types[i%NUMBER_OF_SUITS], King, 10));
        _cards.push_back(Card(types[i%NUMBER_OF_SUITS], Ace, 11)); // or 1
    }

    Shuffle();
}

Card Deck::WithdrawCard()
{
    Card tempCard = _cards.back();
    _cards.pop_back();
    return tempCard;
}

void Deck::Shuffle()
{
    size_t size = _cards.size();

    for (size_t i = 0; i < _cards.size(); ++i)
    {
        int r1;
        do 
        {
            r1 = rand() % size;
        } while (r1 == i);
        

        Utilities::Swap(_cards[r1], _cards[i]);
    }
}
