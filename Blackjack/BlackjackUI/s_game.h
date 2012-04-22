#ifndef S_GAME_H
#define S_GAME_H

#include "state.h"

union ALLEGRO_EVENT;

class S_Game : public State
{
public:
    S_Game() { }
    void Initialize() { }
    void LoadContents() { }
    bool Update(ALLEGRO_EVENT* ev) { return false; }
    void Draw() { }
    void UnloadContents() { }
};

#endif // S_GAME_H
