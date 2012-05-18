/*!
 * \file s_game_over.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#ifndef S_GAME_OVER_H
#define S_GAME_OVER_H

#include "state.h"
#include "fonts.h"
#include "rect_button.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include <vector>

union ALLEGRO_EVENT;

/*!
 * \class S_GameOver
 *
 * \brief Screen that is shown after the game end
 * 
 * This shows some statistics of the game (number of bets, player than won
 * more money and a lot more) and has a button to return to main menu
 *
 */
class S_GameOver : public State
{
public:
    //! Constructor
    S_GameOver() { }
    //! Initialization of some variables
    void Initialize();
    //! Load to memory different files (sounds, images and others). Called after Initialize()
    void LoadContents() { }
    //! Called every time there's a new event, updates the "state"
    bool Update(ALLEGRO_EVENT* ev);
    //! Called when re-drawing the screen is needed. Called after Update()
    void Draw();
    //! Frees the memory of allocated resources in LoadContents()
    void UnloadContents();
private:
    RectButton* _menuButton;
};
#endif // S_GAME_OVER_H
