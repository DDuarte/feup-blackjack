#ifndef BLACKJACKUI_H
#define BLACKJACKUI_H

#include <allegro5/allegro.h>
#define ALLEGRO_STATICLINK

void Error(char const* message); // Move to utilities

enum State
{
    STATE_MAIN_MENU,
    STATE_PLAYING,
    STATE_GAME_OVER,
    STATE_SETTINGS,
};

enum Constants
{
    CONST_WIDTH = 800,
    CONST_HEIGHT = 600,
    CONST_FPS = 60
};

class BlackJackUI
{
public:
    BlackJackUI();
private:
    void Initialize();
    void LoadContents() { }
    void Update() { }
    void Draw();
    void UnloadContents();

    void Quit();

    void _Start();

    ALLEGRO_DISPLAY* _display;
    ALLEGRO_EVENT_QUEUE* _eventQueue;
    ALLEGRO_TIMER* _timer;

    // game 
    int _state;
    bool _done;
    bool _draw;
};

#endif // BLACKJACKUI_H
