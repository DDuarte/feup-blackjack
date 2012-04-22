#ifndef S_GAME_H
#define S_GAME_H

#include "state.h"

union ALLEGRO_EVENT;
struct ALLEGRO_BITMAP;
struct ALLEGRO_FONT;

class S_Game : public State
{
public:
    S_Game();
    void Initialize() { }
    void LoadContents();
    bool Update(ALLEGRO_EVENT* ev) { return true; }
    void Draw();
    void UnloadContents();

private:
    ALLEGRO_BITMAP* _background;
    ALLEGRO_BITMAP* _cardsSprite;
    ALLEGRO_FONT* _font50;
    ALLEGRO_FONT* _font10;
};

#endif // S_GAME_H
