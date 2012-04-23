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
    bool hasAces = false;

    if (_cards.size() == 0)
        // This should only be called by AddCard so hand must have at least 1 element
        throw InvalidCardException("Empty hand at Hand::UpdateScore()!");

    for (std::vector<Card*>::const_iterator card = _cards.begin(); card != _cards.end(); ++card)
        if ((*card)->GetRank() != CARD_RANK_ACE)
            _score += (*card)->GetScore();
        else
            hasAces = true;
    
    for (std::vector<Card*>::const_iterator card = _cards.begin(); card != _cards.end(); ++card)
        if ((*card)->GetRank() == CARD_RANK_ACE)
        {
            if (_score + ACE_MAX_VAL <= BLACKJACK_HAND)
                (*card)->SetScore(ACE_MAX_VAL);
            else
                (*card)->SetScore(ACE_MIN_VAL);

            _score += (*card)->GetScore();
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
    // Draw cards (including "zoomed" ones (when mouse hovered))
    int indexMHCard = -1;
    bool mouseHovered = false;

    for (int i = _cards.size() - 1; i >= 0; --i)
    {
        float x = dx + (i*14);
        float y = dy - (i*15);
        mouseHovered =
            ((BlackJack::GetMousePosition().X <= x + CARD_SIZE.X) && (BlackJack::GetMousePosition().X >= x) &&
            (BlackJack::GetMousePosition().Y <= y + CARD_SIZE.Y) && (BlackJack::GetMousePosition().Y >= y));
        if (mouseHovered)
        {
            indexMHCard = i; 
            break;
        }
    }

    mouseHovered =
        ((BlackJack::GetMousePosition().X <= dx + CARD_SIZE.X) && (BlackJack::GetMousePosition().X >= dx) &&
        (BlackJack::GetMousePosition().Y <= dy + CARD_SIZE.Y) && (BlackJack::GetMousePosition().Y >= dy));

    for (uint i = 0; i < _cards.size(); ++i)
    {
        float x = dx + (i*14);
        float y = dy - (i*15);

        if (cardBack)
            _cards[i]->DrawBack(x, y, angle);
        else
            _cards[i]->Draw(x, y, angle);
    }

    if (indexMHCard != -1)
        if (cardBack)
            _cards[indexMHCard]->DrawBack(dx + (indexMHCard*14), dy - (indexMHCard*15), angle);
        else
            _cards[indexMHCard]->Draw(dx + (indexMHCard*14), dy - (indexMHCard*15), angle, true);

    // Draw score

    al_draw_rectangle(dx - 21, dy - 21, dx + 1, dy + 1, al_map_rgb(255, 255, 255), 2);
    al_draw_textf(Fonts::GetFont(19), al_map_rgb(0, 0, 0), dx - 20, dy - 20, 0, "%2.0i", _score);
}

