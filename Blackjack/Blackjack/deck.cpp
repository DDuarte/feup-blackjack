#include "deck.h"
#include "card.h"

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
}

void Deck::DrawCard()
{

}
