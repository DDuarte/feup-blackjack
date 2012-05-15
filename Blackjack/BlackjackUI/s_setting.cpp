#include "s_settings.h"
#include "bitmaps.h"
#include "localization.h"
#include "rect_button.h"
#include "fonts.h"
#include "s_game.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include <vector>
#include <string>

bool ChangeToMenuState(RectButton* btn);
bool HandleButtonClicked(RectButton* btn);

S_Settings::S_Settings() { }

void S_Settings::Initialize() 
{
    uint x = 100;
    uint y = 100;

    std::vector<Language> languages = Localization::Instance()->GetAvailableLanguages();

    for (uint i = 0; i < languages.size(); ++i)
    {
        int indice = languages[i];
        LanguageButton* temp = new LanguageButton(RectButton(Vector2D(x, y), al_map_rgb(255, 255, 255), LanguageComplete[indice], 50, RectButton::ButtonHandler().Bind<&HandleButtonClicked>(), true), indice);
        _buttons.push_back(temp);
        y += 80;
    }

    RectButton* btn = new RectButton(Vector2D(800-200, 600-120), al_map_rgb(255, 255, 255), std::string("Menu"), 50, RectButton::ButtonHandler().Bind<&ChangeToMenuState>(), true);
    _buttons.push_back(btn);

    RectButton* betUp = new RectButton(Vector2D(34, 15), Vector2D(553, 182), RectButton::ButtonHandler().Bind<&HandleBetUp>());
    RectButton* betDown = new RectButton(Vector2D(34, 15), Vector2D(553, 246), RectButton::ButtonHandler().Bind<&HandleBetDown>());
    _buttons.push_back(betUp);
    _buttons.push_back(betDown);
}

void S_Settings::LoadContents() { }

bool S_Settings::Update(ALLEGRO_EVENT* ev)
{
    for (std::vector<RectButton*>::const_iterator itr = _buttons.begin(); itr != _buttons.end(); ++itr)
        if (!(*itr)->Update(ev))
            break;

    return true;
}

void S_Settings::Draw() 
{
    Bitmap(BITMAP_MENU_BACKGROUND).Draw();

    al_draw_filled_rounded_rectangle(40, 40, 800-40, 600-40, 10, 10, al_map_rgba(0, 0, 0, 175));

    al_draw_textf(Fonts::GetFont(30), al_map_rgb(255,255,255), 800-80, 80, ALLEGRO_ALIGN_RIGHT, "Atual: %s", Localization::Instance()->GetCurrentLanguage().c_str());

    for (std::vector<RectButton*>::const_iterator itr = _buttons.begin(); itr != _buttons.end(); ++itr)
        (*itr)->Draw();

    // Debug printing
    al_draw_textf(Fonts::GetFont(10), al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "x: %3.1f y: %3.1f", BlackJack::GetMousePosition().X, BlackJack::GetMousePosition().Y);

    int ux1 = 570;
    int uy1 = 182;
    int ux2 = ux1 + 17;
    int uy2 = uy1 + 15;
    int ux3 = ux1 - (ux2 - ux1);
    int uy3 = uy2;

    int bx1 = ux1;
    int by1 = 261;
    int bx2 = ux1 + 17;
    int by2 = by1 - 15;
    int bx3 = bx1 - (bx2 - bx1);
    int by3 = by2;

    al_draw_filled_triangle(ux1, uy1, ux2, uy2, ux3, uy3, al_map_rgb(0, 255, 0));
    al_draw_filled_triangle(bx1, by1, bx2, by2, bx3, by3, al_map_rgb(0, 255, 0));

    al_draw_text(Fonts::GetFont(25), al_map_rgb(255, 255, 255), 488, 208, 0, "Aposta:");
    al_draw_textf(Fonts::GetFont(25), al_map_rgb(255, 255, 100), 570, 208, 0, "%2.0f", S_Game::GetBet());
}

bool HandleBetUp(RectButton* btn)
{
    S_Game::SetBet(S_Game::GetBet() + 1);

    return true;
}

bool HandleBetDown(RectButton* btn)
{
    if (S_Game::GetBet() > 1)
        S_Game::SetBet(S_Game::GetBet() - 1);

    return true;
}

void S_Settings::UnloadContents()
{
    for (uint i = 0; i < _buttons.size(); ++i)
        delete _buttons[i];
    
    _buttons.clear();
}

bool HandleButtonClicked(RectButton* btn)
{
    int newLang = ((S_Settings::LanguageButton*)(btn))->GetLanguage();

    if (newLang <= 0)
        return false;

    Localization::Instance()->SetLang((Language)newLang);

    return true;
}

bool ChangeToMenuState(RectButton* btn)
{
    BlackJack::Instance()->ChangeState(STATE_MAIN_MENU);
    return false;
}

