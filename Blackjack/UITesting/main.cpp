#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "../Blackjack/localization.h"

enum State
{
    None,
    MainMenu,
    PlayingField,
    GameOver,
    Settings,
};

const int Width = 800;
const int Height = 600;
const int FPS = 60;

void ChangeState(State& state, State newState)
{ // WIP
    switch (state)
    {
        case MainMenu:
        case PlayingField:
        case GameOver:
        case Settings:
            break;
    }

    state = newState;

    switch (state)
    {
        case MainMenu:
        case PlayingField:
        case GameOver:
        case Settings:
            break;
    }
}

void HandleMainMenu(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* eventQueue)
{
    ALLEGRO_BITMAP* mainMenu = al_load_bitmap("../../Resources/wallpaper.jpg");
    ALLEGRO_FONT* font140 = al_load_font("../../Resources/fonts/Champagne & Limousines.ttf", 140, 0);
    ALLEGRO_FONT* font50 = al_load_font("../../Resources/fonts/Champagne & Limousines.ttf", 50, 0);

    al_reserve_samples(2);
    ALLEGRO_SAMPLE* bgMusic = al_load_sample("../../Resources/sounds/86876__milton__title-screen.ogg");
    ALLEGRO_SAMPLE* nextMenuSound = al_load_sample("../../Resources/sounds/86881_milton_yes.ogg");
    al_play_sample(bgMusic, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    

    bool done = false;
    bool draw = true;

    enum Menu
    {
        Play,
        Settings,
        Quit
    };

    ALLEGRO_COLOR shadowText = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR text = al_map_rgb(200, 200, 200);
    ALLEGRO_COLOR selectedText = al_map_rgb(255, 255, 255);

    int selectedMenu = Play;

    while (!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventQueue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
                selectedMenu = ((selectedMenu + 1) % (Quit + 1));
            else if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
                selectedMenu = selectedMenu == 0 ? Quit : ((selectedMenu - 1) % (Quit + 1));

            al_play_sample(nextMenuSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            draw = true;
        }

        if (draw)
        {
            al_draw_bitmap(mainMenu, 0, 0, 0);                               // background
            al_draw_text(font140, shadowText, Width / 3 + 1, 1, ALLEGRO_ALIGN_CENTRE, "Blackjack");
            al_draw_text(font140, al_map_rgb(255, 255, 255), Width / 3, 0,   // title
                ALLEGRO_ALIGN_CENTRE, "Blackjack");
            

            // shadow
            al_draw_text(font50, shadowText, 51, 441, ALLEGRO_ALIGN_LEFT, "Play");
            al_draw_text(font50, shadowText, 51, 441 + 45, ALLEGRO_ALIGN_LEFT, "Settings");
            al_draw_text(font50, shadowText, 51, 441 + 90, ALLEGRO_ALIGN_LEFT, "Quit");

            // the text
            ALLEGRO_COLOR colorP = selectedMenu == Play ? selectedText : text;
            ALLEGRO_COLOR colorS = selectedMenu == Settings ? selectedText : text;
            ALLEGRO_COLOR colorQ = selectedMenu == Quit ? selectedText : text;

            al_draw_text(font50, colorP, 50, 440, ALLEGRO_ALIGN_LEFT, "Play");
            al_draw_text(font50, colorS, 50, 440 + 45, ALLEGRO_ALIGN_LEFT, "Settings");
            al_draw_text(font50, colorQ, 50, 440 + 90, ALLEGRO_ALIGN_LEFT, "Quit");

            al_flip_display();

            draw = false;
        }
    }

    al_destroy_font(font50);
    al_destroy_font(font140);
    al_destroy_sample(bgMusic);
    al_destroy_sample(nextMenuSound);
    al_destroy_bitmap(mainMenu);
}

int main()
{
    if (!al_init())
        return -1;

    ALLEGRO_DISPLAY* display = al_create_display(Width, Height);
    if (!display)
        return -1;

    // vars
    bool done = false;
    bool redraw = true;
    const int FPS = 60;
    bool isGameOver = false;
    State state = None;

    ALLEGRO_EVENT_QUEUE* eventQueue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    
    // init allegro modules
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_audio();
    al_init_acodec_addon();

    // rand seed
    srand(time(NULL));

    // events
    eventQueue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));

    // misc
    al_hide_mouse_cursor(display);

    al_start_timer(timer);
    // ChangeState(state, MainMenu)
    HandleMainMenu(display, eventQueue);

    al_destroy_display(display);                                    // destroy display
    return 0;                                                       // exit
}