#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "player.h"

#include <vector>
#include <queue>

const unsigned int NUM_ACTIVE_PLAYERS= 4;

class BlackJack : public Game
{
public:

private:
    std::vector<Player> _players;
    std::queue<*Player> _waitingPlayers;

    Player* _activePlayers[NUM_ACTIVE_PLAYERS];

    Dealer _dealer;
    Deck _deck;
};

#endif // BLACKJACK_H