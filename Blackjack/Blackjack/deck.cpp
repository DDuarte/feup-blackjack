#include "utilities.h"
#include "deck.h"
#include "card.h"

#include <ctime>
#include <stack>
#include <vector>

Deck::Deck()
{
    InitializeDeck(DEFAULT_NUMBER_OF_DECKS);
}

Deck::Deck(unsigned int numberOfDecks)
{
    InitializeDeck(numberOfDecks);
}

void Deck::InitializeDeck( unsigned int numberOfDecks )
{
    _cards = std::vector<Card>();

    _cards.reserve(52*numberOfDecks);

    CardSuit types[] = { Clubs, Spades, Hearts, Diamonds };

    for (int i = 0; i < 4; ++i)
    {
        _cards.push_back(Card(types[i%numberOfDecks], Two, 2));
        _cards.push_back(Card(types[i%numberOfDecks], Three, 3));
        _cards.push_back(Card(types[i%numberOfDecks], Four, 4));
        _cards.push_back(Card(types[i%numberOfDecks], Five, 5));
        _cards.push_back(Card(types[i%numberOfDecks], Six, 6));
        _cards.push_back(Card(types[i%numberOfDecks], Seven, 7));
        _cards.push_back(Card(types[i%numberOfDecks], Eight, 8));
        _cards.push_back(Card(types[i%numberOfDecks], Nine, 9));
        _cards.push_back(Card(types[i%numberOfDecks], Ten, 10));
        _cards.push_back(Card(types[i%numberOfDecks], Jack, 10));
        _cards.push_back(Card(types[i%numberOfDecks], Queen, 10));
        _cards.push_back(Card(types[i%numberOfDecks], King, 10));
        _cards.push_back(Card(types[i%numberOfDecks], Ace, 11)); // or 1
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
