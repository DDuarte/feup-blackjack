#ifndef STATE_H_
#define STATE_H_

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

#endif // STATE_H_
