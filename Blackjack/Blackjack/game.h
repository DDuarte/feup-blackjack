#ifndef GAME_H
#define GAME_H

class Game abstract
{
public:
    virtual void Initialize() { };
    virtual void LoadContents() { };
    virtual void Update() { };
    virtual void Draw() { };
    virtual void UnloadContents() { };
};

#endif // GAME_H
