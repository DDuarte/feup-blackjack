#ifndef S_GAME_H
#define S_GAME_H

#include "state.h"
#include "utilities.h"

#include <vector>
#include <queue>

union ALLEGRO_EVENT;
struct ALLEGRO_BITMAP;
class Deck;
class Player;
class Dealer;
class RectButton;

enum GameState
{
    GAME_STATE_PLACING_BETS,
    GAME_STATE_DEALING_CARDS,
    GAME_STATE_PLAYER_TURN,
    GAME_STATE_DEALER_TURN,
    GAME_STATE_CHECK_RESULTS,
    GAME_STATE_RESET_ROUND,
    GAME_STATE_POST_GAME
};

const uint MAX_ACTIVE_PLAYERS = 4;

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
    void PlayerBet(Player* /* player*/) { /*_totalBets += bet;*/ /* ... */ }
    void PlayerHit(Player* player);
    void PlayerStand(Player* player);
    void PlayerDouble(Player* player);
    // void PlayerSurrender(Player* player) { }

    static Player** GetActivePlayers() { return _activePlayers; }
    static int GetActivePlayerIndex() { return _activePlayerIndex; }

    void DealerHit(Dealer* dealer) { }
    void DealerStand(Dealer* dealer) { }

    void HandleOutOfCards() { }

    static double GetBet() { return _bet; }

    ALLEGRO_BITMAP* GetChip() { return _chip; }

private:
    ALLEGRO_BITMAP* _background;
    ALLEGRO_BITMAP* _chip;

    Dealer* _dealer;
    Deck* _deck;

    std::vector<Player> _players;
    std::queue<Player*> _waitingPlayers;
    static Player** _activePlayers;
    int _activePlayerCount;
    
    int _gameState;
    static int _activePlayerIndex;

    uint _tempCounter;

    std::vector<RectButton*> _buttons;
    
    bool HandleStatePlacingBets();   // Initial placement of bets
    bool HandleStateDealingCards();  // Dealer deals cards
    bool HandleStatePlayerTurn();    // Players make hit, stand or double
    bool HandleStateDealerTurn();    // Dealer Hits until 17
    bool HandleStateCheckResults();  // Checks the result of the game and pays to the players or not
    bool HandleStateResetRound();       // Resets
    bool HandleStatePostGame() { return true; }     // Handle player surrender, etc.
    
    void ReadPlayersFromFile();

    void SelectPlayers();
    void NextPlayer();
    Player* SelectNextPlayerFromQueue();

    static double _bet;
    void NextInternalGameState();
};

#endif // S_GAME_H
