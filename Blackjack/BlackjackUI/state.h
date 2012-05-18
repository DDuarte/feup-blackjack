/*!
 * \file state.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#ifndef STATE_H
#define STATE_H

union ALLEGRO_EVENT;

/*!
 * \class State
 *
 * \brief Abstract class that defines an application state
 *
 */
class State
{
public:
    //! Initialization of some variables
    virtual void Initialize() = 0;
    //! Load to memory different files (sounds, images and others). Called after Initialize()
    virtual void LoadContents() = 0;
    //! Called every time there's a new event, updates the "state"
    virtual bool Update(ALLEGRO_EVENT* ev) = 0;
    //! Called when re-drawing the screen is needed. Called after Update()
    virtual void Draw() = 0;
    //! Frees the memory of allocated resources in LoadContents()
    virtual void UnloadContents() = 0;
};

#endif // STATE_H
