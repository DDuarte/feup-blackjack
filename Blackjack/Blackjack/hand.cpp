#include "hand.h"
#include "card.h"
#include "gameExceptions.h"

#include <vector>

Hand::Hand()
{
    _cards = std::vector<Card>();
    _score = 0;
}

Hand::Hand(std::vector<Card> cards)
{
    _cards = cards;
    _score = 0;
}

void Hand::AddCard(Card card)
{
    if (card.IsValid())
    {
        _cards.push_back(card);
        UpdateScore();
    }
    else
        throw InvalidCardException("Invalid card at Hand::AddCard(Card card)!");
}

void Hand::UpdateScore()
{
    // TODO: Test

    int aces = 0;

    for (std::vector<Card>::const_iterator card = _cards.begin(); card != _cards.end(); ++card)
    {
        if (card->GetName() == Ace)
        {
            aces++;
            continue;
        }
        else
            _score += card->GetScore();
    }

    for (int i = 0; i < aces; ++i)
    {
        if (_score + ACE_MAX_VAL <= BLACKJACK_HAND)
            _score += ACE_MAX_VAL;
        else
            _score += ACE_MIN_VAL;
    }
}
