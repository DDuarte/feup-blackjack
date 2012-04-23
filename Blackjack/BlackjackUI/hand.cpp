#include "hand.h"
#include "card.h"
#include "gameExceptions.h"
#include "utilities.h"

#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/mouse.h>

Hand::Hand()
{
    _cards = std::vector<Card*>();
    _score = 0;
}

Hand::~Hand()
{
    for (size_t i = 0; i < _cards.size(); ++i)
        delete _cards[i];
}

Hand& Hand::AddCard(Card* card)
{
    if (card->IsValid())
    {
        _cards.push_back(card);
        UpdateScore();
        return *this;
    }
    else
        throw InvalidCardException("Invalid card at Hand::AddCard(Card card)!");
}

void Hand::UpdateScore()
{
    // TODO: Test

    if (_cards.size() == 0)
        // This should only be called by AddCard so hand must have at least 1 element
        throw InvalidCardException("Empty hand at Hand::UpdateScore()!");

    int aces = 0;

    for (std::vector<Card*>::const_iterator card = _cards.begin(); card != _cards.end(); ++card)
    {
        if ((*card)->GetRank() == CARD_RANK_ACE)
        {
            aces++;
            continue;
        }
        else
            _score += (*card)->GetScore();
    }

    for (int i = 0; i < aces; ++i)
    {
        if (_score + ACE_MAX_VAL <= BLACKJACK_HAND)
            _score += ACE_MAX_VAL;
        else
            _score += ACE_MIN_VAL;
    }
}

void Hand::RemoveCard(const Card* card)
{
    std::vector<Card*>::iterator itr = std::find(_cards.begin(), _cards.end(), card);

    if (itr == _cards.end())
        return; // Throw except?

    _cards.erase(itr);

    if (_cards.size() > 0)
        UpdateScore();
}

void Hand::Clear()
{
    for (size_t i = 0; i < _cards.size(); ++i)
        delete _cards[i];

    _cards.clear();

    _score = 0;
}

void Hand::Draw(float dx, float dy, float angle /*= 0.0*/, bool cardBack /*= false*/)
{
    Card* mouseHoveredCard = NULL;
    uint indexMHCard = 0;

    for (uint i = 0; i < _cards.size(); ++i)
    {
        float x = dx + (i*14);
        float y = dy - (i*15);

        if (cardBack)
            _cards[i]->DrawBack(x, y, angle);
        else
            _cards[i]->Draw(x, y, angle);

        if (_cards[i]->IsMouseHovered())
        {
            mouseHoveredCard = _cards[i];
            indexMHCard = i;
        }
    }

    if (mouseHoveredCard)
        if (cardBack)
            mouseHoveredCard->DrawBack(dx + (indexMHCard*14), dy - (indexMHCard*15), angle);
        else
            mouseHoveredCard->Draw(dx + (indexMHCard*14), dy - (indexMHCard*15), angle);
}

