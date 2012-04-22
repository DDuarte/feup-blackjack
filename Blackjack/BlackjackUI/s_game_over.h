#ifndef S_GAME_OVER_H
#define S_GAME_OVER_H

#include "state.h"

struct ALLEGRO_EVENT_QUEUE;

class S_GameOver : public State
{
public:
    S_GameOver() { }
    void Initialize() { }
    void LoadContents() { }
    bool Update(ALLEGRO_EVENT_QUEUE* evQueue) { return true; }
    void Draw() { }
    void UnloadContents() { }
};

#endif // S_GAME_OVER_H
