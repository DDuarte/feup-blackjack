#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "game.h"
#include "player.h"
#include "deck.h"

#include <vector>
#include <queue>

const unsigned int NUM_ACTIVE_PLAYERS = 4;

class Deck;
class Player;

class BlackJack : public Game
{
public:
    BlackJack();
    ~BlackJack();

    void RegisterPlayer(std::string name, double balance);
    std::vector<Player*> CheckWinners() const;

    virtual void Initialize();
    virtual void LoadContents() { }
    virtual void Update() { }
    virtual void Draw() { }
    virtual void UnloadContents() { }

    void ReadPlayersFromFile();

    void RemovePlayer(Player* player);
    void VerifyPlayersBalance();

    bool ShouldEnd();
    bool CanStart();

    // Events-like calls
    void PlayerBet(Player* /* player*/, double bet) { _totalBets += bet; }
    // void PlayerHit(Player* player);
    // void PlayerStand(Player* player);
    // void PlayerDouble(Player* player);
    // void PlayerSurrender(Player* player);

private:
    std::vector<Player> _players;

    std::queue<Player*> _waitingPlayers;
    Player** _activePlayers;

    void SelectPlayers(); // For the first 4 players
    Player* SelectNextPlayer(); // For each "replacement"

    Deck* _deck;

    double _totalBets; // TODO: This needs to be distributed to players on round (?) end and
                       // also updated with players bets
};

#endif // BLACKJACK_H
