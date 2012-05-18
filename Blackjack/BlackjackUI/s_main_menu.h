/*!
 * \file s_main_menu.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

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

/*!
 * \class S_MainMenu
 *
 * \brief Main menu of the game (Play, Options, Quit)
 *
 */
class S_MainMenu : public State
{
public:
    //! Constructor
    S_MainMenu();
    //! Initialization of some variables
    void Initialize();
    //! Load to memory different files (sounds, images and others). Called after Initialize()
    void LoadContents();
    //! Called every time there's a new event, updates the "state"
    bool Update(ALLEGRO_EVENT* ev);
    //! Called when re-drawing the screen is needed. Called after Update()
    void Draw();
    //! Frees the memory of allocated resources in LoadContents()
    void UnloadContents();

private:
    RectButton* _playButton;
    RectButton* _settingButton;
    RectButton* _quitButton;

    int _selectedMenu;
};

#endif // S_MAIN_MENU_H
