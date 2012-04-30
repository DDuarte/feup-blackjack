#ifndef STATE_H
#define STATE_H

union ALLEGRO_EVENT;

class State
{
public:
    virtual void Initialize() = 0;
    virtual void LoadContents() = 0;
    virtual bool Update(ALLEGRO_EVENT* ev) = 0;
    virtual void Draw() = 0;
    virtual void UnloadContents() = 0;
};

#endif // STATE_H
