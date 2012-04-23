#include "deck.h"
#include "s_game.h"
#include "card.h"
#include "blackjack.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/mouse.h>

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

    // Testing method draw of card
    Card(rand() % 4, rand() % 13, 0).Draw(BlackJack::Instance()->GetDisplay(), 82, 217, 0);
    Card(rand() % 4, rand() % 13, 0).Draw(BlackJack::Instance()->GetDisplay(), 82+14, 217, 0);

    Card(rand() % 4, rand() % 13, 0).Draw(BlackJack::Instance()->GetDisplay(), 260, 344, 0);
    Card(rand() % 4, rand() % 13, 0).Draw(BlackJack::Instance()->GetDisplay(), 260+14, 344, 0);

    Card(rand() % 4, rand() % 13, 0).Draw(BlackJack::Instance()->GetDisplay(), 517, 344, 0);
    Card(rand() % 4, rand() % 13, 0).Draw(BlackJack::Instance()->GetDisplay(), 517+14, 344, 0);

    Card(rand() % 4, rand() % 13, 0).Draw(BlackJack::Instance()->GetDisplay(), 652, 217, 0);
    Card(rand() % 4, rand() % 13, 0).Draw(BlackJack::Instance()->GetDisplay(), 652+14, 217, 0);

    // Testing method draw and withdrawcard of deck
    _deck.Draw(595, 33, true);
    _deck.WithdrawCard();

    // debug printing
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);
    al_draw_textf(_font10, al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "x: %i y: %i", state.x, state.y);
}

void S_Game::UnloadContents()
{
    al_destroy_bitmap(_background);
    al_destroy_font(_font50);
    al_destroy_font(_font10);

    Card::DestroyBitmaps();
}


