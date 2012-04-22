#ifndef S_SETTINGS_H
#define S_SETTINGS_H

#include "state.h"

struct ALLEGRO_EVENT_QUEUE;

class S_Settings : public State
{
public:
    S_Settings() { }
    void Initialize() { }
    void LoadContents() { }
    bool Update(ALLEGRO_EVENT_QUEUE* evQueue) { return true; }
    void Draw() { }
    void UnloadContents() { }
};

#endif // S_SETTINGS_H
