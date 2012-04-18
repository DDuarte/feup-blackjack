#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "game.h"

#include <vector>
#include <queue>

const unsigned int NUM_ACTIVE_PLAYERS = 4;

class Dealer;
class Deck;
class Player;

class BlackJack : public Game
{
public:
    BlackJack();
    ~BlackJack();

    void RegisterPlayer(std::string name, double balance);

    virtual void Initialize();
    virtual void LoadContents();
    virtual void Update();
    virtual void Draw();
    virtual void UnloadContents();

private:
    std::vector<Player> _players;
    std::queue<Player*> _waitingPlayers;

    Player** _activePlayers;

    void SelectPlayers();

    // Should these two be pointers?
    Dealer* _dealer;
    Deck* _deck;
};

#endif // BLACKJACK_H