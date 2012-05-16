#include "blackjack.h"
#include "utilities.h"
#include "s_settings.h"
#include "s_game.h"
#include "s_game_over.h"
#include "s_main_menu.h"
#include "fonts.h"
#include "card.h"
#include "sounds.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <time.h>
#include <vector>

BlackJack* BlackJack::_instance = NULL; 
ALLEGRO_MOUSE_STATE* BlackJack::_mouseState = new ALLEGRO_MOUSE_STATE;

BlackJack* BlackJack::Instance()
{
    if (!_instance)
        _instance = new BlackJack;

    return _instance;
}

BlackJack::BlackJack()
{
    _display = NULL;
    _eventQueue = NULL;
    _timer = NULL;
    

    _state = -1;
    _done = false;
    _draw = true;

    _states = std::vector<State*>();
}

void BlackJack::Initialize()
{
    // inits
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    _display = al_create_display(CONST_WIDTH, CONST_HEIGHT);
    if (!_display)
        Error("Failed to initialize display.");

    al_set_system_mouse_cursor(_display, ALLEGRO_SYSTEM_MOUSE_CURSOR_PROGRESS);
    // mouse is reseted before entering the game loop

    if (!al_init_primitives_addon()) Error("Failed to initialize primitives addon.");
    al_init_font_addon();
    if (!al_init_ttf_addon()) Error("Failed to initialize ttf addon.");
    if (!al_init_image_addon()) Error("Failed to initialize image addon.");
    if (!al_install_keyboard()) Error("Failed to install keyboard.");
    if (!al_install_mouse()) Error("Failed to install mouse.");
    if (!al_install_audio()) Error("Failed to install audio.");
    if (!al_init_acodec_addon()) Error("Failed to initialize acodec addon.");

    // events
    _eventQueue = al_create_event_queue();
    _timer = al_create_timer(1.0 / CONST_FPS);
    al_register_event_source(_eventQueue, al_get_keyboard_event_source());
    al_register_event_source(_eventQueue, al_get_mouse_event_source());
    al_register_event_source(_eventQueue, al_get_display_event_source(_display));
    al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));

    // miscs
    srand((unsigned int)time(NULL));
    //al_hide_mouse_cursor(_display);

    _states.push_back(new S_MainMenu);
    _states.push_back(new S_Settings);
    _states.push_back(new S_Game);
    _states.push_back(new S_GameOver);

    //for (std::vector<State*>::const_iterator itr = _states.begin(); itr != _states.end(); ++itr)
    //    (*itr)->Initialize(); done when changing states
    _mute = false;
    ChangeState(STATE_MAIN_MENU);
}

void BlackJack::LoadContents()
{
    //for (std::vector<State*>::const_iterator itr = _states.begin(); itr != _states.end(); ++itr)
    //    (*itr)->LoadContents(); done when changing states

    al_set_system_mouse_cursor(_display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
}

void BlackJack::Update(ALLEGRO_EVENT* ev)
{
    al_get_mouse_state(_mouseState);
    _draw = _states[_state]->Update(ev);
}

void BlackJack::Draw()
{
    _draw = false;

    _states[_state]->Draw();

    al_flip_display();
}

void BlackJack::UnloadContents()
{
    _states[_state]->UnloadContents(); // Nothing else is calling UnlCont for the last state

    for (std::vector<State*>::const_iterator itr = _states.begin(); itr != _states.end(); ++itr)
    {
        if ((*itr) == NULL)
            continue;

        // (*itr)->UnloadContents(); done when changing states
        delete (*itr);
    }

    al_destroy_event_queue(_eventQueue);
    al_destroy_timer(_timer);

    al_destroy_display(_display);

    Fonts::UnloadFonts();
    Bitmaps::UnloadBitmaps();
    Sounds::UnloadSounds();

    delete _mouseState; // only one instance of this class exists
}

bool BlackJack::Quit(bool promptUser/*= false*/)
{
    int result = (promptUser ? al_show_native_message_box(BlackJack::Instance()->GetDisplay(), "Sair", "", "Deseja sair?", NULL, ALLEGRO_MESSAGEBOX_QUESTION|ALLEGRO_MESSAGEBOX_OK_CANCEL) : true);
    _done = !(result == 2 || result == 0);
    return _done;
}

void BlackJack::_Start()
{
    Initialize();
    LoadContents();

    al_start_timer(_timer);
    while (!_done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(_eventQueue, &ev); // blocking

        Update(&ev);

        // Only draw if something was changed
        if (_draw /*&& al_event_queue_is_empty(_eventQueue)*/)
            Draw();
    }

    UnloadContents();
}

void BlackJack::ChangeState(int newState)
{
    al_flip_display();
    al_clear_to_color(al_map_rgb(0,0,0));

    if (_state != -1)
        _states[_state]->UnloadContents();

    Sounds::StopAllSounds();
    Bitmaps::UnloadBitmaps();
    Fonts::UnloadFonts();

    _state = newState;

    _states[_state]->Initialize();
    _states[_state]->LoadContents();
}
