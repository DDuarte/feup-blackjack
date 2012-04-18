#include "hand.h"
#include "card.h"
#include "gameExceptions.h"

#include <vector>

Hand::Hand()
{
    _cards = std::vector<Card>();
}

Hand::Hand( std::vector<Card> cards )
{
    _cards = std::vector<Card>();
    _cards.reserve(cards.size());
    _cards = cards;
}


unsigned int Hand::GetScore()
{
    unsigned int score = 0;
    bool hasAce = false;
    for (std::vector<Card>::const_iterator card = _cards.begin(); card != _cards.end(); ++card)
    {
        if (card->GetName() !=  Ace)
            score += card->GetScore();
        else
            hasAce = true;
    }

    if (hasAce)
        for (std::vector<Card>::iterator card = _cards.begin(); card != _cards.end(); ++card)
        {
            if (card->GetName() ==  Ace)
                if (score + 11 > 21)
                { 
                    card->SetScore(11);
                    score += 11;
                }
                else
                {
                    card->SetScore(1);
                    score += 1;
                }
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



