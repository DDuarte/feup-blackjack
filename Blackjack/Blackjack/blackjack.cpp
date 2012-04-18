#include "blackjack.h"
#include "player.h"
#include "deck.h"
#include "gameExceptions.h"

#include <exception>

BlackJack::BlackJack()
{
    _players = std::vector<Player>();
    _waitingPlayers = std::queue<Player*>();

    _activePlayers = new Player*[NUM_ACTIVE_PLAYERS];

    _deck = new Deck;
}

BlackJack::~BlackJack()
{
    UnloadContents();

    // ...

    delete[] _activePlayers;

    delete _deck;

    _players.clear();

    while (!_waitingPlayers.empty())
        _waitingPlayers.pop();

}

void BlackJack::SelectPlayers()
{
    if (_waitingPlayers.empty() || _waitingPlayers.size() < NUM_ACTIVE_PLAYERS)
        throw InvalidPlayerException("Not enough players to start a game."); // TODO: Change this to a custom exception
                                                                            // We need to catch it later and print error
                                                                           // to player

    for (unsigned int i = 0; i < NUM_ACTIVE_PLAYERS; ++i)
    {
        _activePlayers[i] = _waitingPlayers.front();
        _waitingPlayers.pop();
    }
}

void BlackJack::RegisterPlayer(std::string name, double balance)
{
    if (balance <= 0 || name.empty())
        throw InvalidPlayerException("Invalid parameters when registering player."); // TODO: (Read above exception comment)

    _players.push_back(Player(name, balance));
    _waitingPlayers.push(&_players.back());
    
}


std::vector<Player*> BlackJack::CheckWinners() const
{
    std::vector<Player*> winners;
    for (int i = 0; i < NUM_ACTIVE_PLAYERS; ++i)
    {
        if (!winners.empty())
        {
            if (winners.at(0)->GetHand().GetScore() < _activePlayers[i]->GetHand().GetScore())
                winners.clear();
            else if (winners.at(0)->GetHand().GetScore() > _activePlayers[i]->GetHand().GetScore())
                continue;
        }
        winners.push_back(_activePlayers[i]);
    }
    return winners;
}


void BlackJack::Initialize()
{

}

void BlackJack::LoadContents()
{

}

void BlackJack::Update()
{

}

void BlackJack::Draw()
{

}

void BlackJack::UnloadContents()
{

}
