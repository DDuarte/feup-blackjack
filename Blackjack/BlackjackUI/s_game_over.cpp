#include "s_game_over.h"
#include "bitmap.h"

void S_GameOver::Draw()
{
    al_draw_text(Fonts::GetFont(100), al_map_rgb(255,255,255), 400, 250, ALLEGRO_ALIGN_CENTRE, "Game Over");
    Bitmap(BITMAP_MENU_GAME_OVER).Draw();
}