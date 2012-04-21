#include "blackjackUI.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <time.h>

void Error(char const* message)
{
    al_show_native_message_box(NULL, "Error", NULL, message, NULL, ALLEGRO_MESSAGEBOX_ERROR);
    exit(EXIT_FAILURE);
}

BlackJackUI::BlackJackUI()
{
    _display = NULL;
    _eventQueue = NULL;
    _timer = NULL;

    _state = -1;
    _done = false;
    _draw = true;

    _Start();
}

void BlackJackUI::Initialize()
{
    // inits
    _display = al_create_display(CONST_WIDTH, CONST_HEIGHT);
    if (!_display)
        Error("Failed to initialize display.");

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
    al_hide_mouse_cursor(_display);
}

void BlackJackUI::UnloadContents()
{
    al_destroy_event_queue(_eventQueue);
    al_destroy_timer(_timer);

    al_destroy_display(_display);
}

void BlackJackUI::Quit()
{
    _done = true;
    // Anything else?
}

void BlackJackUI::_Start()
{
    Initialize();
    LoadContents();

    while (!_done)
    {
        Update();
        Draw();
    }

    UnloadContents();
}

void BlackJackUI::Draw()
{
    if (!_draw)
        return;

    _draw = true;

    // ...
}
