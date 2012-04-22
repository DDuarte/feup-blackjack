#ifndef S_GAME_OVER_H
#define S_GAME_OVER_H

#include "state.h"

union ALLEGRO_EVENT;

class S_GameOver : public State
{
public:
    S_GameOver() { }
    void Initialize() { }
    void LoadContents() { }
    bool Update(ALLEGRO_EVENT* ev) { return false; }
    void Draw() { }
    void UnloadContents() { }
};

#endif // S_GAME_OVER_H
