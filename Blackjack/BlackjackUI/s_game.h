#ifndef S_GAME_H
#define S_GAME_H

#include "state.h"
#include "utilities.h"
#include "bitmaps.h"

#include <vector>
#include <queue>

union ALLEGRO_EVENT;
struct ALLEGRO_BITMAP;
struct ALLEGRO_SAMPLE;
class Deck;
class Player;
class Dealer;
class RectButton;
class ICardOwner;
class TextLog;
class Card;

enum GameState
{
    GAME_STATE_PLACING_BETS,
    GAME_STATE_DEALING_CARDS,
    GAME_STATE_PLAYER_TURN,
    GAME_STATE_DEALER_TURN,
    GAME_STATE_CHECK_RESULTS,
    GAME_STATE_STAY_OR_GIVE_UP,
    GAME_STATE_POST_GAME,
    GAME_STATE_RESET_ROUND
};

enum Buttons
{
    BUTTON_HIT,
    BUTTON_STAND,
    BUTTON_DOUBLE,
    BUTTON_GIVE_UP,
    BUTTON_STAY_GAME
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
    void PlayerBet(Player* /* player*/);
    void PlayerHit(Player* player, Card* card);
    void PlayerStand(Player* player);
    void PlayerDouble(Player* player, Card* card);
    void PlayerSurrender(Player* player);
    void PlayerStay(Player* player);

    void DealerHit(Dealer* dealer, Card* card);

    Player** GetActivePlayers() { return _activePlayers; }
    int GetActivePlayerIndex() { return _activePlayerIndex; }

    void HandleOutOfCards() { }

    static double GetBet() { return _bet; }

    ALLEGRO_BITMAP* GetChip() { return Bitmaps::GetBitmap(BITMAP_GAME_CHIP); }

private:
    ALLEGRO_SAMPLE* _dealCardSound;
    ALLEGRO_SAMPLE* _doubleSound;
    ALLEGRO_SAMPLE* _dealerBlackjackSound;

    Dealer* _dealer;
    Deck* _deck;

    std::vector<Player> _players;
    std::queue<Player*> _waitingPlayers;
    Player** _activePlayers;
    
    int _gameState;
    int _activePlayerIndex;

    std::vector<RectButton*> _buttons;
    
    bool HandleStatePlacingBets();   // Initial placement of bets
    bool HandleStateDealingCards(uint i);  // Dealer deals cards
    bool HandleStatePlayerTurn();    // Players make hit, stand or double
    bool HandleStateDealerTurn();    // Dealer Hits until 17
    bool HandleStateCheckResults();  // Checks the result of the game and pays to the players or not
    bool HandleStateStayOrGiveUp();  // Asks the player if staying or giving up
    bool HandleStatePostGame();      // Handles player removal
    bool HandleStateResetRound();    // Resets
    
    void ReadPlayersFromFile();

    void SelectPlayers();
    Player* SelectNextPlayerFromQueue();

    static double _bet;
    void NextInternalGameState();
    bool _playerPlayed;

    int CountActivePlayers() const;

    TextLog* _log;
};

#endif // S_GAME_H
