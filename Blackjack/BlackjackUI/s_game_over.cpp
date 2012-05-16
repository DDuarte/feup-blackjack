#include "s_game_over.h"
#include "bitmap.h"
#include "blackjack.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

bool S_GameOver::Update(ALLEGRO_EVENT* ev)
{
    return true;
}

void S_GameOver::Draw()
{
    al_draw_text(Fonts::GetFont(100), al_map_rgb(255,255,255), 400, 250, ALLEGRO_ALIGN_CENTRE, "Game Over");
    static Bitmap bg (BITMAP_MENU_GAME_OVER);

    // Debug printing
    al_draw_textf(Fonts::GetFont(10), al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "x: %3.1f y: %3.1f", BlackJack::GetMousePosition().X, BlackJack::GetMousePosition().Y);

    // outer rectangle
    al_draw_rectangle(80.0, 160.0, 720.0, 468.0, al_map_rgb(255, 255, 255), 1.0);
}
