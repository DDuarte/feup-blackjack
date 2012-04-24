#ifndef S_GAME_H
#define S_GAME_H

#include "state.h"
#include "deck.h"
#include "dealer.h"
#include "rectButton.h"

#include <vector>
#include <queue>

union ALLEGRO_EVENT;
struct ALLEGRO_BITMAP;

class Player;

enum GameState
{
    GAME_STATE_PLACING_BETS,
    GAME_STATE_DEALING_CARDS,
    GAME_STATE_PLAYER_TURN,
    GAME_STATE_DEALER_TURN,
    GAME_STATE_RESET_ROUND,
    GAME_STATE_POST_GAME
};

const uint NUM_ACTIVE_PLAYERS = 4;

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

    Deck* GetDeck() { return _deck; }

    //- Game specific
    // Events-like calls
    void PlayerBet(Player* /* player*/, double bet) { /*_totalBets += bet;*/ /* ... */ }
    void PlayerHit(Player* player);
    void PlayerStand(Player* player) { }
    void PlayerDouble(Player* player) { }
    // void PlayerSurrender(Player* player) { }

    static Player** GetActivePlayers() { return _activePlayers; }
    static int GetActivePlayerIndex() { return _activePlayerIndex; }

    void DealerHit(Dealer* dealer) { }
    void DealerStand(Dealer* dealer) { }

    void HandleOutOfCards() { }

private:
    ALLEGRO_BITMAP* _background;

    Dealer* _dealer;
    Deck* _deck;

    std::vector<Player> _players;
    std::queue<Player*> _waitingPlayers;
    static Player** _activePlayers;
    int _activePlayerCount;
    
    int _gameState;
    static int _activePlayerIndex;

    std::vector<RectButton*> _buttons;
    
    bool HandleStatePlacingBets();   // Initial placement of bets
    bool HandleStateDealingCards() { return true; }  // Dealer deals cards
    bool HandleStatePlayerTurn() { return true; }    // Players make hit, stand or double
    bool HandleStateDealerTurn() { return true; }    // Dealer Hits and checks for winning hands or not
    bool HandleStateResetRound();       // Resets
    bool HandleStatePostGame() { return true; }     // Handle player surrender, etc.

    void ReadPlayersFromFile();

    void SelectPlayers();
    Player* SelectNextPlayerFromQueue();
};

#endif // S_GAME_H
