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

void Dealer::Draw()
{
    static const char* name = "Dealer";

    al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 255, 255),
        DEALER_POSITION.X + 10, DEALER_POSITION.Y + 10 + 105, 0, name);

    if (IsBusted())
        al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 242, 0),
        DEALER_POSITION.X + 10, DEALER_POSITION.Y + 30 + 105, 0, "Busted");
    else if (IsBlackjack())
        al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 242, 0),
        DEALER_POSITION.X + 10, DEALER_POSITION.Y + 30 + 105, 0, "BlackJack");
    else if (_game->GetState() > GAME_STATE_DEALER_TURN)
        al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 242, 0),
        DEALER_POSITION.X + 10, DEALER_POSITION.Y + 30 + 105, 0, "Stand");

    _hand.Draw();
}

void Dealer::NewCard( Card* card )
{
    _hand.AddCard(card);
}

bool Dealer::Hit()
{
    if (Card* card = _game->GetDeck()->WithdrawCard())
    {
        NewCard(card);
        _game->DealerHit(this, card);
    }
    else
        _game->HandleOutOfCards();
    return true;
}
