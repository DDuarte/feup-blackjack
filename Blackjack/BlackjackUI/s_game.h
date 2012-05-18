#ifndef S_GAME_H
#define S_GAME_H

#include "state.h"
#include "utilities.h"
#include "bitmaps.h"
#include "player.h"

#include <vector>
#include <queue>

union ALLEGRO_EVENT;
struct ALLEGRO_BITMAP;
class Deck;
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
const uint MIN_ACTIVE_PLAYERS = 2;

/*!
 * \struct Stats
 *
 * \brief Statistics that will be shown in the game over screen
 *
 */
struct Stats
{
    Stats()
    {
        TotalMoneyBetPlayers = TotalMoneyReceivedPlayers = 0;
        BlackjackCount = BustedCount = DoubleCount = HitCount = BetCount = StandCount = RoundCount = 0;
        Winner = PlayerWonMoreMoney = PlayerLostMoreMoney = NULL;
    }

    double TotalMoneyBetPlayers;
    double TotalMoneyReceivedPlayers;
    int BlackjackCount;
    int BustedCount;
    int DoubleCount;
    int HitCount;
    int BetCount;
    int StandCount;
    int RoundCount;

    std::vector<Player> Players;
    Player* Winner;
    Player* PlayerWonMoreMoney;
    Player* PlayerLostMoreMoney;

    void CalculateWinners()
    {
        if (Players.empty())
            return;

        Player* tempWinner = &(*Players.begin());
        Player* tempLoser = &(*Players.begin());
        for (std::vector<Player>::iterator itr = Players.begin(); itr != Players.end(); ++itr)
        {
            if (tempWinner->GetBalanceDiff() < (*itr).GetBalanceDiff())
                tempWinner = &(*itr);

            if (tempLoser->GetBalanceDiff() > (*itr).GetBalanceDiff())
                tempLoser = &(*itr);
        }

        PlayerWonMoreMoney = tempWinner;
        PlayerLostMoreMoney = tempLoser;
    }
};

/*!
 * \class S_Game
 *
 * \brief Play game state. Contains the game logic and the game data.
 *
 */
class S_Game : public State
{
public:
    //- State specific
    //! Game Play State constructor
    S_Game();
    //! Initialization of some variables
    void Initialize();
    //! Load to memory different files (sounds, images and others). Called after Initialize()
    void LoadContents();
    //! Called every time there's a new event, updates the "state"
    bool Update(ALLEGRO_EVENT* ev);
    //! Called when re-drawing the screen is needed. Called after Update()
    void Draw();
    //! Frees the memory of allocated resources in LoadContents()
    void UnloadContents();

    //! Returns the deck
    Deck* GetDeck() { return _deck; }

    //- Game specific
    // Events-like calls
    //! Handles the player bet event. It is called by player bet method of the player class.
    void PlayerBet(Player* /* player*/);
    //! Handles the player hit event. It is called by player hit method of the player class.
    void PlayerHit(Player* player, Card* card);
    //! Handles the player stand event. It is called by player stand method of the player class.
    void PlayerStand(Player* player);
    //! Handles the player double event. It is called by player double method of the player class.
    void PlayerDouble(Player* player, Card* card);
    //! Handles the player surrender event. It is called by player surrender method of the player class every time a player gives up after a round.
    void PlayerSurrender(Player* player);
    //! Handles the player stay event. It is called by player stay method of the player class every time a player stays after a round.
    void PlayerStay(Player* player);

    //! Handles the dealer hit event. It is called by the hit method of the Dealer class.
    void DealerHit(Dealer* dealer, Card* card);

    //! Returns an array with pointers to the player in the table (active players)
    Player** GetActivePlayers() { return _activePlayers; }
    //! Returns the index of the player that is currently playing
    int GetActivePlayerIndex() { return _activePlayerIndex; }
    //! Return the current internal game state
    int GetState() { return _gameState; }
    //! Returns a pointer to the dealer
    Dealer* GetDealer() { return _dealer; }

    //! Return the bet
    static double GetBet() { return _bet; }
    //! Sets the bet
    static void SetBet(double bet) { _bet = bet; }

    //! Returns the game chip ALLEGRO_BITMAP*
    ALLEGRO_BITMAP* GetChip() { return Bitmaps::GetBitmap(BITMAP_GAME_CHIP); }

    //! Stats instance for the game over state
    static Stats Statistics;

private:
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
    void UpdatePlayersFile() const;

    void SelectPlayers();
    Player* SelectNextPlayerFromQueue();

    static double _bet;
    void NextInternalGameState();
    bool _playerPlayed;

    int CountActivePlayers() const;


    TextLog* _log;
};

#endif // S_GAME_H
