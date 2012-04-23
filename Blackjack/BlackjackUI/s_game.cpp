#include "deck.h"
#include "s_game.h"
#include "card.h"
#include "blackjack.h"
#include "hand.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/mouse.h>

#include <Windows.h>

S_Game::S_Game()
{
    _background = NULL;
    _font50 = NULL;
    _font10 = NULL;
}

void S_Game::Initialize()
{
    _deck = Deck();
}

void S_Game::LoadContents()
{
    _background = al_load_bitmap("../../Resources/playing_table.png");
    _font50 = al_load_font("../../Resources/fonts/Champagne & Limousines.ttf", 50, 0);
    _font10 = al_load_font("../../Resources/fonts/Champagne & Limousines.ttf", 10, 0);
}

void S_Game::Draw()
{
    al_draw_bitmap(_background, 0, 0, 0);

    // Testing method draw of card and draw of hand
    
    Hand h;
    h.AddCard(new Card(rand() % 4, rand() % 13, 0))
    .AddCard(new Card(rand() % 4, rand() % 13, 0))
    .AddCard(new Card(rand() % 4, rand() % 13, 0))
    .Draw(82, 217, 0);

    Hand h2;
    h2.AddCard(new Card(CARD_SUIT_CLUBS, CARD_RANK_JACK, 0))
    .AddCard(new Card(CARD_SUIT_HEARTS, CARD_RANK_TWO, 0))
    .Draw(260, 344, 0);

    Hand h3;
    h3.AddCard(new Card(rand() % 4, rand() % 13, 0))
    .AddCard(new Card(rand() % 4, rand() % 13, 0))
    .AddCard(new Card(rand() % 4, rand() % 13, 0))
    .AddCard(new Card(rand() % 4, rand() % 13, 0))
    .Draw(517, 344, 0);

    Hand h4;
    h4.AddCard(new Card(rand() % 4, rand() % 13, 0));
    h4.Draw(652, 217, 0);

    // Testing method draw and withdrawcard of deck
    _deck.Draw(595, 33, true);
    _deck.WithdrawCard();

    Sleep(500);

    // debug printing
    
    al_draw_textf(_font10, al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "x: %i y: %i", BlackJack::GetMousePosition().X, BlackJack::GetMousePosition().Y);
}

void S_Game::UnloadContents()
{
    al_destroy_bitmap(_background);
    al_destroy_font(_font50);
    al_destroy_font(_font10);

    Card::DestroyBitmaps();
}


