#include "deck.h"
#include "s_game.h"
#include "card.h"
#include "blackjack.h"
#include "hand.h"
#include "fonts.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

S_Game::S_Game()
{
    _background = NULL;
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

    // Testing method draw of card and draw of hand
    
    Hand h;
    h.AddCard(new Card(rand() % 4, rand() % 13))
    .AddCard(new Card(rand() % 4, rand() % 13))
    .AddCard(new Card(rand() % 4, rand() % 13))
    .Draw(82, 217, 0);

    Hand h2;
    h2.AddCard(new Card(CARD_SUIT_CLUBS, CARD_RANK_ACE))
    .AddCard(new Card(CARD_SUIT_HEARTS, CARD_RANK_ACE))
    .AddCard(new Card(CARD_SUIT_SPADES, CARD_RANK_ACE))
    .AddCard(new Card(CARD_SUIT_DIAMONDS, CARD_RANK_KING))
    .Draw(260, 344, 0);

    Hand h3;
    h3.AddCard(new Card(rand() % 4, rand() % 13))
    .AddCard(new Card(rand() % 4, rand() % 13))
    .AddCard(new Card(rand() % 4, rand() % 13))
    .AddCard(new Card(rand() % 4, rand() % 13))
    .Draw(517, 344, 0);

    Hand h4;
    h4.AddCard(new Card(rand() % 4, rand() % 13));
    h4.Draw(652, 217, 0);

    // Testing method draw and withdrawcard of deck
    _deck.Draw(595, 33, true);
    _deck.WithdrawCard();

    Sleep(500);

    // debug printing
    al_draw_textf(Fonts::GetFont(10), al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "x: %3.1f y: %3.1f", BlackJack::GetMousePosition().X, BlackJack::GetMousePosition().Y);
}

void S_Game::UnloadContents()
{
    al_destroy_bitmap(_background);


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
