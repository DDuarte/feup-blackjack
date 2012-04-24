#ifndef S_GAME_H
#define S_GAME_H

#include "state.h"
#include "deck.h"
#include "dealer.h"

union ALLEGRO_EVENT;
struct ALLEGRO_BITMAP;

class Player;

class S_Game : public State
{
public:
    //- State specific
    S_Game();
    void Initialize();
    void LoadContents();
    bool Update(ALLEGRO_EVENT* ev);
    void Draw();
    void UnloadContents();

    Deck* GetDeck() { return &_deck; }

    //- Game specific
    // Events-like calls
    void PlayerBet(Player* /* player*/, double bet) { /*_totalBets += bet;*/ /* ... */ }
    void PlayerHit(Player* player);
    void PlayerStand(Player* player) { }
    void PlayerDouble(Player* player) { }
    // void PlayerSurrender(Player* player) { }

    void DealerHit(Dealer* dealer) { }
    void DealerStand(Dealer* dealer) { }

    void HandleOutOfCards() { }

private:
    ALLEGRO_BITMAP* _background;

    Dealer* _dealer;
    Deck _deck;
    
};

#endif // S_GAME_H
