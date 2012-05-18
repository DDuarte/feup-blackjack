/*!
 * \file blackjack.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "utilities.h"
#include "sounds.h"
#include <vector>

#include <allegro5/allegro.h>

enum StateEnum
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
class State;

/*!
 * \class BlackJack
 *
 * \brief Handles game states
 *
 *  Handles game stats (main menu, settings, game, game over) and contains the
 *  main loop (while !done -> update, draw)
 *  
 *  Singleton, single instance (BlackJack::Instance())
 *
 */
class BlackJack
{
public:
    //! Static access to the object
    static BlackJack* Instance();
    //! Current mouse position
    static Vector2D GetMousePosition() { return Vector2D(_mouseState->x, _mouseState->y); }
    //! Start of all the process
    void _Start();
    //! Quits the application
    bool Quit(bool prompteUser = false);

    //! Changes state
    void ChangeState(int newState);

    //! Tells if sound should be muted or not
    bool GetMute() const { return _mute; }
    //! Mutes or unmutes sounds
    void SetMute(bool mute) { _mute = mute; if (mute) Sounds::StopAllSounds(); }

    //! Access to ALLEGRO_DISPLAY
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

    // game loop & states
    int _state;
    bool _done;
    bool _draw;
    bool _mute;

    std::vector<State*> _states;
};

#endif // BLACKJACKUI_H
