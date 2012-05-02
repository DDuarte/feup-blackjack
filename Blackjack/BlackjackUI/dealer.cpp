#include "s_game.h"
#include "dealer.h"
#include "hand.h"
#include "deck.h"
#include "fonts.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

Dealer::Dealer(S_Game* game)
{
    _game = game;
    _hand = Hand(DEALER_POSITION, true);
}

void Dealer::Hit()
{
    Card* tempCard = _game->GetDeck()->WithdrawCard();

    if (tempCard != NULL)
    {
        _hand.AddCard(tempCard);
        _game->DealerHit(this);
    }
    else
        _game->HandleOutOfCards();
}

void Dealer::Stand()
{
    _game->DealerHit(this);
}

void Dealer::Draw()
{
    const char* name = "Dealer";

    al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 255, 255),
        DEALER_POSITION.X + 10, DEALER_POSITION.Y + 10 + 105, 0, name);

    _hand.Draw();
}
