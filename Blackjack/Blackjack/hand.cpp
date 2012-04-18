#include "hand.h"
#include "card.h"

#include <vector>

Hand::Hand()
{


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


void Hand::AddCard( Card card )
{
    if (card.IsValid())
    {
        _cards.push_back(card);
    }
    else
    {

    }
}



