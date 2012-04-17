#ifndef GAME_H
#define GAME_H

abstract class Game
{
public:
    Game();

    ~Game();
   
protected:
    Initialize();
    LoadContents();
    Update();
    Draw();
    UnloadContents();
private:

};

#endif // GAME_H