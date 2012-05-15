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
    void Draw();
    void UnloadContents() { }
};

#endif // S_GAME_OVER_H
