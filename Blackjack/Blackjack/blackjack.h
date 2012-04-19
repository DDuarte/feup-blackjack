#ifndef BLACKJACK_H
#define BLACKJACK_H


#include "utilities.h"
#include "game.h"
#include "player.h"
#include "deck.h"

#include <vector>
#include <queue>

const uint NUM_ACTIVE_PLAYERS = 4;

class Deck;
class Player;

class BlackJack : public Game
{
public:
    BlackJack();
    ~BlackJack();

    //void RegisterPlayer(std::string name, double balance);
    std::vector<Player*> CheckWinners() const;

    virtual void Initialize();
    virtual void LoadContents() { }
    virtual void Update() { }
    virtual void Draw() { }
    virtual void UnloadContents();

    Deck* GetDeck() { return &_deck; }

    void ReadPlayersFromFile();
    void WritePlayersToFile();

    void VerifyPlayersBalance();

    bool ShouldEnd();
    bool CanStart() { return _waitingPlayers.size() >= NUM_ACTIVE_PLAYERS && _activePlayerCount == 0; }

    void Start();
    void NextPlayer() { _currentPlayerIndex = (_currentPlayerIndex + 1) % 4; }
    void HandleOutOfCards() { }

    int RegisteredPlayerCount() { return _players.size(); }
    int WaitingPlayerCount() { return _waitingPlayers.size(); }
    int ActivePlayerCount() { return _activePlayerCount; }

    // Events-like calls
    void PlayerBet(Player* /* player*/, double bet) { _totalBets += bet; /* ... */ }
    void PlayerHit(Player* player) { }
    void PlayerStand(Player* player) { }
    void PlayerDouble(Player* player);
    // void PlayerSurrender(Player* player);

private:
    // Application Variables
    std::vector<Player> _players;
    std::queue<Player*> _waitingPlayers;

    // Game Variables
    Player** _activePlayers;
    int _activePlayerCount;
    uint _currentPlayerIndex;


    void SelectPlayers(); // For the first 4 players
    Player* SelectNextPlayerFromQueue(); // For each "replacement"
    void CountActivePlayers();

    void AddPlayer(const Player& player);
    void RemovePlayer(Player* player);

    Deck _deck;

    double _totalBets; // TODO: This needs to be distributed to players on round (?) end and
                       // also updated with players bets
};

#endif // BLACKJACK_H
