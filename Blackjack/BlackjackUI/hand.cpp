#include "hand.h"
#include "card.h"
#include "gameExceptions.h"
#include "utilities.h"
#include "blackjack.h"
#include "fonts.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include <vector>
#include <algorithm>

Hand::Hand(Vector2D position, bool dealerHand /*= false*/)
{
    _cards = std::vector<Card*>();
    _score = 0;
    _dealerHand = dealerHand;
    _drawSecondCardBack = dealerHand;
    _cardJustAdded = -1;
    _position = position;
}

Hand::Hand()
{
    _cards = std::vector<Card*>();
    _score = 0;
    _dealerHand = false;
    _drawSecondCardBack = _dealerHand;
    _cardJustAdded = -1;
    _position = Vector2D(0,0);
}

Hand& Hand::AddCard(Card* card) // Returning a reference to this
{                               // so we can chain multiple add cards
    if (!card)
        return *this;
    
    if (!card->IsValid())
        throw InvalidCardException("Invalid card at Hand::AddCard(Card card)!");
    
    _cards.push_back(card);
    UpdateScore();
    _cardJustAdded = _cards.size() - 1;

    return *this;
}

void Hand::UpdateScore()
{
    int aceCount = 0;
    _score = 0;

    if (_cards.size() == 0)
        // This should only be called by AddCard so hand *must* have at least 1 element
        throw InvalidCardException("Empty hand at Hand::UpdateScore()!");

    for (std::vector<Card*>::const_iterator card = _cards.begin(); card != _cards.end(); ++card)
    {
        if ((*card)->GetRank() != CARD_RANK_ACE)
            _score += (*card)->GetScore();
        else
            aceCount++;
    }
    
    // special point calculation for aces, value of ace is 11 or 1, depending on what benefits the player most
    if (aceCount > 0)
    {
        for (std::vector<Card*>::const_iterator card = _cards.begin(); card != _cards.end(); ++card)
        {
            if ((*card)->GetRank() == CARD_RANK_ACE)
            {
                (*card)->SetScore((_score + ACE_MAX_VAL*aceCount <= BLACKJACK_HAND) ? ACE_MAX_VAL : ACE_MIN_VAL);
                _score += (*card)->GetScore();
                aceCount--;
            }
        }
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
    _cards.clear();

    _score = 0;
}

void Hand::Draw()
{
    if (!IsPositionSet())
        return;

    // Draw cards (including "zoomed" ones (when mouse hovered))
    int indexMHCard = -1;

    float angle = 0.0;

    for (int i = _cards.size() - 1; i >= 0; --i)
    {
        float x = _position.X + (i*14);
        float y = _position.Y - (i*15*!_dealerHand);
        if ((BlackJack::GetMousePosition().X <= x + CARD_SIZE.X) && (BlackJack::GetMousePosition().X >= x) &&
            (BlackJack::GetMousePosition().Y <= y + CARD_SIZE.Y) && (BlackJack::GetMousePosition().Y >= y))
        {
            indexMHCard = i; 
            break;
        }
    }

    for (uint i = 0; i < _cards.size(); ++i)
    {
        float x = _position.X + i * 14;
        float y = _position.Y - i * 15 * !_dealerHand;

        if (_dealerHand && _drawSecondCardBack && i == 1)
            _cards[i]->DrawBack(x, y, angle);
        else
        {
            _cards[i]->Draw(x, y, angle, _cardJustAdded == i);
            _cardJustAdded = -1;
        }
    }

    if (indexMHCard != -1)
    {
        float x = _position.X + indexMHCard * 14;
        float y = _position.Y - indexMHCard * 15 * !_drawSecondCardBack;

        if (_drawSecondCardBack && indexMHCard == 1)
            _cards[indexMHCard]->DrawBack(x, y, angle);
        else
            _cards[indexMHCard]->Draw(x, y, angle, true);
    }

    // Draw score of hand if no card is hidden and if score is not zero
    if (!_dealerHand && _score > 0 /* && _cards.size() != 0*/)
    {
        al_draw_filled_rectangle(_position.X - 21, _position.Y - 21, _position.X + 1, _position.Y + 1, al_map_rgb(255, 255, 255));
        al_draw_textf(Fonts::GetFont(19), al_map_rgb(0, 0, 0), _position.X - 20, _position.Y - 20, 0, "%2.0i", _score);
    }
}
