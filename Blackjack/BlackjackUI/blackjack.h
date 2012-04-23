#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "state.h"
#include "utilities.h"

#include <vector>

#include <allegro5/allegro.h>

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
union ALLEGRO_EVENT;


// Singleton, single instance
class BlackJack // : public State
{
public:
    static BlackJack* Instance();
    static Vector2D GetMousePosition() { return Vector2D(_mouseState->x, _mouseState->y); }
    void _Start();
    void Quit();

    void ChangeState(int newState);

    ALLEGRO_DISPLAY* GetDisplay() { return _display; }
private:
    BlackJack();
    static BlackJack* _instance;
    static ALLEGRO_MOUSE_STATE* _mouseState;

    void Initialize();
    void LoadContents();
    void Update(ALLEGRO_EVENT* ev);
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
