#ifndef S_SETTINGS_H
#define S_SETTINGS_H

#include "state.h"
#include "rect_button.h"
#include "localization.h"

#include <vector>

union ALLEGRO_EVENT;

class S_Settings : public State
{
    friend bool HandleButtonClicked(RectButton* btn);
    class LanguageButton : public RectButton
    {
        public:
            LanguageButton(const RectButton& btn) : RectButton(btn), Language(-1) { }
            LanguageButton(const RectButton& btn, int lang) : RectButton(btn), Language(lang) { }

            int Language;
    };

public:
    S_Settings();
    void Initialize();
    void LoadContents();
    bool Update(ALLEGRO_EVENT* ev);
    void Draw();
    void UnloadContents();

private:
    std::vector<RectButton*> _buttons;
};


#endif // S_SETTINGS_H
