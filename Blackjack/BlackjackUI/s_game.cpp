#include "deck.h"
#include "s_game.h"
#include "card.h"
#include "blackjack.h"
#include "hand.h"
#include "fonts.h"
#include "dealer.h"
#include "player.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

S_Game::S_Game()
{
    _background = NULL;
    _dealer = new Dealer(this);
}

void S_Game::Initialize()
{
    _deck = Deck();
}

void S_Game::LoadContents()
{
    _background = al_load_bitmap("../../Resources/playing_table.png");
}

void S_Game::Draw()
{
    al_draw_bitmap(_background, 0, 0, 0);
    al_flip_display();

    if (!_deck.GetGameCardsNumber())
        return;

    // Testing method draw of card and draw of hand and get cards from a deck
    Hand h5(265, 63, true);
    h5.AddCard(_deck.WithdrawCard());

    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(_background, 0, 0, 0);
    h5.Draw();

    h5.AddCard(_deck.WithdrawCard());

    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(_background, 0, 0, 0);
    h5.Draw();

    Hand h(82, 217);
    h.AddCard(_deck.WithdrawCard());

    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(_background, 0, 0, 0);
    h.Draw();
    h5.Draw();

    h.AddCard(_deck.WithdrawCard());

    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(_background, 0, 0, 0);
    h.Draw();
    h5.Draw();

    Hand h2(260, 344);
    h2.AddCard(_deck.WithdrawCard());

    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(_background, 0, 0, 0);
    h.Draw();
    h2.Draw();
    h5.Draw();

    h2.AddCard(_deck.WithdrawCard());

    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(_background, 0, 0, 0);
    h.Draw();
    h2.Draw();
    h5.Draw();

    Hand h3(517, 344);
    h3.AddCard(_deck.WithdrawCard());

    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(_background, 0, 0, 0);
    h.Draw();
    h2.Draw();
    h3.Draw();
    h5.Draw();

    h3.AddCard(_deck.WithdrawCard());

    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(_background, 0, 0, 0);
    h.Draw();
    h2.Draw();
    h3.Draw();
    h5.Draw();

    Hand h4(652, 217);
    h4.AddCard(_deck.WithdrawCard());

    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(_background, 0, 0, 0);
    h.Draw();
    h2.Draw();
    h3.Draw();
    h4.Draw();
    h5.Draw();

    h4.AddCard(_deck.WithdrawCard());

    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(_background, 0, 0, 0);
    h.Draw();
    h2.Draw();
    h3.Draw();
    h4.Draw();
    h5.Draw();

    // Testing method draw and withdrawcard of deck
    _deck.Draw(595, 33, true);
    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(_background, 0, 0, 0);
    h.Draw();
    h2.Draw();
    h3.Draw();
    h4.Draw();
    h5.Draw();
    Sleep(500);

    // debug printing
    al_draw_textf(Fonts::GetFont(10), al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "x: %3.1f y: %3.1f", BlackJack::GetMousePosition().X, BlackJack::GetMousePosition().Y);
}

void S_Game::UnloadContents()
{
    al_destroy_bitmap(_background);

    delete _dealer;
    Card::DestroyBitmaps();
}

bool S_Game::Update(ALLEGRO_EVENT* ev)
{
    if (!ev)
        return false;

    switch (ev->type)
    {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
        {
            BlackJack::Instance()->Quit();
            return false;
        }
        case ALLEGRO_EVENT_KEY_UP:
        {
            if (ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                BlackJack::Instance()->Quit();
                return false;
            }
            break;
        }
        case ALLEGRO_EVENT_TIMER:
            return true; // draw every 1/60 secs
    }

    return false;
}

void S_Game::PlayerHit(Player* player)
{
    if (player->IsBusted())
    {
        player->Lose();
    }
}


