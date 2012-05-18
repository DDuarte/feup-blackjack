/*!
 * \file s_settings.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#ifndef S_SETTINGS_H
#define S_SETTINGS_H

#include "state.h"
#include "rect_button.h"
#include "localization.h"

#include <vector>

union ALLEGRO_EVENT;

bool HandleBetUp(RectButton* btn);
bool HandleBetDown(RectButton* btn);

/*!
 * \class S_Settings
 *
 * \brief Settings screen (muting sound, changing language, changing minimum bet, ...)
 *
 */
class S_Settings : public State
{
    //! Called when a button is clicked
    friend bool HandleButtonClicked(RectButton* btn);

    /*!
     * \class LanguageButton
     *
     * \brief Defines a language button. Clicking it changes the app language.
     *
     */
    class LanguageButton : public RectButton
    {
    public:
        //! Constructor
        LanguageButton(const RectButton& btn) : RectButton(btn), _language(-1) { }
        //! Constructor
        LanguageButton(const RectButton& btn, int lang) : RectButton(btn), _language(lang) { }
        //! Returns the language represented by this button
        int GetLanguage() const { return _language; }

    private:
        int _language;
    };

public:
    //! Constructor
    S_Settings();
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
    std::vector<RectButton*> _buttons;
};


#endif // S_SETTINGS_H
