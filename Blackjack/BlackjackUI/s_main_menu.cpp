#include "s_main_menu.h"
#include "blackjack.h"
#include "card.h"
#include "fonts.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

S_MainMenu::S_MainMenu()
{
    _background = NULL;
    _bgMusic = NULL;
    _nextMenuSound = NULL;
    _selectedMenu = -1;
}

void S_MainMenu::Initialize()
{
    _selectedMenu = MENU_PLAY;
}

void S_MainMenu::LoadContents()
{
    _background = al_load_bitmap("../../Resources/wallpaper.jpg");

    al_reserve_samples(2);
    _bgMusic = al_load_sample("../../Resources/sounds/86876__milton__title-screen.ogg");
    _nextMenuSound = al_load_sample("../../Resources/sounds/86881_milton_yes.ogg");

    al_play_sample(_bgMusic, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

bool S_MainMenu::Update(ALLEGRO_EVENT* ev)
{
    if (!ev)
        return false;

    switch (ev->type)
    {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
        {
            BlackJack::Instance()->Quit();
            return false;
        }
        case ALLEGRO_EVENT_KEY_UP:
        {
            if (ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                BlackJack::Instance()->Quit();
                return false;
            }
            else if (ev->keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                if (_selectedMenu == MENU_PLAY)
                {
                    BlackJack::Instance()->ChangeState(STATE_PLAYING);
                    return true;
                }
                else if (_selectedMenu == MENU_SETTINGS)
                {
                    BlackJack::Instance()->ChangeState(STATE_SETTINGS);
                    return true;
                }
                else if (_selectedMenu == MENU_QUIT)
                {
                    BlackJack::Instance()->Quit();
                    return false;
                }
            }
            break;
        }
        case ALLEGRO_EVENT_KEY_DOWN:
        {
            int add;
            if (ev->keyboard.keycode == ALLEGRO_KEY_DOWN)
                add = 1;
            else if (ev->keyboard.keycode == ALLEGRO_KEY_UP)
                add = -1;
            else
                return false;

            // _selectedMenu will always be in the range [0, 2]
            _selectedMenu = (((_selectedMenu + add) == -1) ? MENU_QUIT : ((_selectedMenu + add) % (MENU_QUIT + 1)));

            al_play_sample(_nextMenuSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            return true;
        }
        case ALLEGRO_EVENT_TIMER:
            return true; // draw every 1/60 secs
    }

    return false;
}

void S_MainMenu::Draw()
{
    ALLEGRO_COLOR shadowText = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR text = al_map_rgb(200, 200, 200);
    ALLEGRO_COLOR selectedText = al_map_rgb(255, 255, 255);

    al_draw_bitmap(_background, 0, 0, 0);
    al_draw_text(Fonts::GetFont(140), shadowText, 267, 1, ALLEGRO_ALIGN_CENTRE, "Blackjack");
    al_draw_text(Fonts::GetFont(140), selectedText, 266, 0, ALLEGRO_ALIGN_CENTRE, "Blackjack");

    // shadow
    al_draw_text(Fonts::GetFont(50), shadowText, 51, 441, ALLEGRO_ALIGN_LEFT, "Play");
    al_draw_text(Fonts::GetFont(50), shadowText, 51, 441 + 45, ALLEGRO_ALIGN_LEFT, "Settings");
    al_draw_text(Fonts::GetFont(50), shadowText, 51, 441 + 90, ALLEGRO_ALIGN_LEFT, "Quit");

    // the text
    ALLEGRO_COLOR colorP = _selectedMenu == MENU_PLAY ? selectedText : text;
    ALLEGRO_COLOR colorS = _selectedMenu == MENU_SETTINGS ? selectedText : text;
    ALLEGRO_COLOR colorQ = _selectedMenu == MENU_QUIT ? selectedText : text;

    al_draw_text(Fonts::GetFont(50), colorP, 50, 440, ALLEGRO_ALIGN_LEFT, "Play");
    al_draw_text(Fonts::GetFont(50), colorS, 50, 440 + 45, ALLEGRO_ALIGN_LEFT, "Settings");
    al_draw_text(Fonts::GetFont(50), colorQ, 50, 440 + 90, ALLEGRO_ALIGN_LEFT, "Quit");
}

void S_MainMenu::UnloadContents()
{
    al_destroy_bitmap(_background);
    al_destroy_sample(_bgMusic);
    al_destroy_sample(_nextMenuSound);
}
