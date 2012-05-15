#include "s_settings.h"
#include "bitmaps.h"
#include "localization.h"
#include "rect_button.h"
#include "fonts.h"

#include <vector>
#include <string>

bool ChangeToMenuState(RectButton* btn);
bool HandleButtonClicked( RectButton* btn );

S_Settings::S_Settings() { }

void S_Settings::Initialize() 
{
    uint x = 100;
    uint y = 100;

    std::vector<Language> l = Localization::Instance()->GetAvailableLanguages();

    for (int i = 0; i < Localization::Instance()->GetAvailableLanguages().size(); i++)
    {
        int indice = Localization::Instance()->GetAvailableLanguages()[i];
        LanguageButton* temp = new LanguageButton(RectButton(Vector2D(x,y),al_map_rgb(255,255,255),LanguageComplete[indice],100,RectButton::ButtonHandler().Bind<&HandleButtonClicked>(),true),indice);
        _buttons.push_back(temp);
        y += 100;
    }

    RectButton* btn = new RectButton (Vector2D(x,y), al_map_rgb(255,255,255), std::string("Menu"), 100,RectButton::ButtonHandler().Bind<&ChangeToMenuState>(),true);
    _buttons.push_back(btn);
}

void S_Settings::LoadContents() { }

bool S_Settings::Update( ALLEGRO_EVENT* ev )
{
    for (std::vector<RectButton*>::iterator i = _buttons.begin(); i != _buttons.end(); i++)
    {
        (*i)->Update(ev);
    }

    return true;
}

void S_Settings::Draw() 
{
    Bitmap(BITMAP_MENU_BACKGROUND).Draw();

    for (std::vector<RectButton*>::iterator i = _buttons.begin(); i != _buttons.end(); i++)
    {
        (*i)->Draw(false);
    }
}

void S_Settings::UnloadContents() { }

bool HandleButtonClicked( RectButton* btn )
{
    int newLang = ((S_Settings::LanguageButton*)(btn))->Language;

    if (newLang == -1) return false;

    Localization::Instance()->SetLang((Language)newLang);

    return true;
}

bool ChangeToMenuState(RectButton* btn)
{
    BlackJack::Instance()->ChangeState(STATE_MAIN_MENU);
    return true;
}