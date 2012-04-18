#include "hand.h"
#include "card.h"
#include "gameExceptions.h"

#include <vector>

Hand::Hand()
{
    _cards.clear();
}

unsigned int Hand::GetScore()
{
    unsigned int score = 0;

    for (std::vector<Card>::const_iterator card = _cards.begin(); card != _cards.end(); ++card)
    {
        score += card->GetScore();
    }

    return score;
}


void Hand::AddCard(Card card)
{
    if (card.IsValid())
    {
        _cards.push_back(card);
    }
    else
    {
        throw InvalidCardException("Invalid card at Hand::AddCard(Card card)!");
    }
}



