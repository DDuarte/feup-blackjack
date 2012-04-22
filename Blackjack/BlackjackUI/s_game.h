#ifndef S_GAME_H
#define S_GAME_H

#include "state.h"

struct ALLEGRO_EVENT_QUEUE;

class S_Game : public State
{
public:
    S_Game() { }
    void Initialize() { }
    void LoadContents() { }
    bool Update(ALLEGRO_EVENT_QUEUE* evQueue) { return true; }
    void Draw() { }
    void UnloadContents() { }
};

#endif // S_GAME_H
