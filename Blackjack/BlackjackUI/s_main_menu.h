#ifndef S_MAIN_MENU_H
#define S_MAIN_MENU_H

#include "state.h"

struct ALLEGRO_BITMAP;
struct ALLEGRO_FONT;
struct ALLEGRO_SAMPLE;

enum Menu
{
    MENU_PLAY,
    MENU_SETTINGS,
    MENU_QUIT,
};

struct ALLEGRO_EVENT_QUEUE;

class S_MainMenu : public State
{
public:
    S_MainMenu();
    void Initialize();
    void LoadContents();
    bool Update(ALLEGRO_EVENT_QUEUE* evQueue);
    void Draw();
    void UnloadContents();
private:
    ALLEGRO_BITMAP* _background;
    ALLEGRO_FONT* _font140;
    ALLEGRO_FONT* _font50;
    ALLEGRO_SAMPLE* _bgMusic;
    ALLEGRO_SAMPLE* _nextMenuSound;

    int _selectedMenu;
};

#endif // S_MAIN_MENU_H
