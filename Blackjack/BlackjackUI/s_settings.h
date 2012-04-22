#ifndef S_SETTINGS_H
#define S_SETTINGS_H

#include "state.h"

union ALLEGRO_EVENT;

class S_Settings : public State
{
public:
    S_Settings() { }
    void Initialize() { }
    void LoadContents() { }
    bool Update(ALLEGRO_EVENT* ev) { return false; }
    void Draw() { }
    void UnloadContents() { }
};

#endif // S_SETTINGS_H
