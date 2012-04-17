#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "player.h"

#include <vector>
#include <queue>
class BlackJack : public Game
{
public:

private:
    std::vector<Player> _players;
    std::queue<*Player> _waitingPlayers;


};

#endif // BLACKJACK_H