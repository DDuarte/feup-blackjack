#include "utilities.h"
#include "deck.h"
#include "card.h"


#include <ctime>

Deck::Deck()
{
    _cards = std::vector<Card>();
    _cards.reserve(52);

    CardSuit types[] = { Clubs, Spades, Hearts, Diamonds };

    for (int i = 0; i < 4; ++i)
    {
        _cards.push_back(Card(types[i], Two, 2));
        _cards.push_back(Card(types[i], Three, 3));
        _cards.push_back(Card(types[i], Four, 4));
        _cards.push_back(Card(types[i], Five, 5));
        _cards.push_back(Card(types[i], Six, 6));
        _cards.push_back(Card(types[i], Seven, 7));
        _cards.push_back(Card(types[i], Eight, 8));
        _cards.push_back(Card(types[i], Nine, 9));
        _cards.push_back(Card(types[i], Ten, 10));
        _cards.push_back(Card(types[i], Jack, 10));
        _cards.push_back(Card(types[i], Queen, 10));
        _cards.push_back(Card(types[i], King, 10));
        _cards.push_back(Card(types[i], Ace, 11)); // or 1
    }
    
    Shuffle();
}

void Deck::DrawCard()
{

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
