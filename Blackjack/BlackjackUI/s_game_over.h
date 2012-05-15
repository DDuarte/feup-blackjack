#ifndef S_GAME_OVER_H
#define S_GAME_OVER_H

#include "state.h"
#include "fonts.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

union ALLEGRO_EVENT;

class S_GameOver : public State
{
public:
    S_GameOver() { }
    void Initialize() { }
    void LoadContents() { }
    bool Update(ALLEGRO_EVENT* ev) { return true; }
    void Draw() { al_draw_text(Fonts::GetFont(100), al_map_rgb(255,255,255), 400, 250, ALLEGRO_ALIGN_CENTRE, "Game Over"); }
    void UnloadContents() { }
};

#endif // S_GAME_OVER_H
