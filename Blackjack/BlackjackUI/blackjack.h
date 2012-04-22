#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "state.h"

#include <vector>

enum GameState
{
    STATE_MAIN_MENU,
    STATE_SETTINGS,
    STATE_PLAYING,
    STATE_GAME_OVER,
};

enum Constants
{
    CONST_WIDTH = 800,
    CONST_HEIGHT = 600,
    CONST_FPS = 60
};

struct ALLEGRO_DISPLAY;
struct ALLEGRO_EVENT_QUEUE;
struct ALLEGRO_TIMER;

// Singleton, single instance
class BlackJack // : public State
{
public:
    static BlackJack* Instance();
    void _Start();
    void Quit();

private:
    BlackJack();
    static BlackJack* _instance;

    void Initialize();
    void LoadContents();
    void Update();
    void Draw();
    void UnloadContents();

    ALLEGRO_DISPLAY* _display;
    ALLEGRO_EVENT_QUEUE* _eventQueue;
    ALLEGRO_TIMER* _timer;

    // game loop
    int _state;
    bool _done;
    bool _draw;
    std::vector<State*> _states;
};

#endif // BLACKJACKUI_H
