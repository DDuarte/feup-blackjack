#ifndef S_MAIN_MENU_H
#define S_MAIN_MENU_H

#include "state.h"

#include <vector>

enum Menu
{
    MENU_PLAY,
    MENU_SETTINGS,
    MENU_QUIT,
};

union ALLEGRO_EVENT;
class RectButton;
class AllegroObject;
struct ALLEGRO_BITMAP;
struct ALLEGRO_SAMPLE;

class S_MainMenu : public State
{
public:
    S_MainMenu();
    void Initialize();
    void LoadContents();
    bool Update(ALLEGRO_EVENT* ev);
    void Draw();
    void UnloadContents();

private:
    ALLEGRO_SAMPLE* _bgMusic;
    ALLEGRO_SAMPLE* _nextMenuSound;

    RectButton* _playButton;
    RectButton* _settingButton;
    RectButton* _quitButton;

    int _selectedMenu;
};

#endif // S_MAIN_MENU_H
