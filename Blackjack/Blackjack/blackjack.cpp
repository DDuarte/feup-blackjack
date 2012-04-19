#include "blackjack.h"
#include "player.h"
#include "deck.h"
#include "hand.h"
#include "localization.h"
#include "gameExceptions.h"

#include <exception>
#include <fstream>

BlackJack::BlackJack()
{
    _players = std::vector<Player>();
    _waitingPlayers = std::queue<Player*>();

    _activePlayers = new Player*[NUM_ACTIVE_PLAYERS];

    _deck = new Deck;

    _totalBets = 0.0;

    Initialize();
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
        throw InvalidPlayerException("Not enough players to start a game."); 

    for (unsigned int i = 0; i < NUM_ACTIVE_PLAYERS; ++i)
    {
        _activePlayers[i] = _waitingPlayers.front();
        _waitingPlayers.pop();
    }
}

void BlackJack::RegisterPlayer(std::string name, double balance)
{
    if (balance <= 0 || name.empty())
        throw InvalidPlayerException("Invalid parameters when registering player.");

    _players.push_back(Player(name, balance, this));
    _waitingPlayers.push(&_players.back());
}


std::vector<Player*> BlackJack::CheckWinners() const
{
    std::vector<Player*> winners = std::vector<Player*>();
    for (int i = 0; i < NUM_ACTIVE_PLAYERS; ++i)
    {
        if (!winners.empty())
        {
            if (winners[0]->GetHand()->GetScore() < _activePlayers[i]->GetHand()->GetScore())
                winners.clear();
            else if (winners[0]->GetHand()->GetScore() > _activePlayers[i]->GetHand()->GetScore())
                continue;
        }
        winners.push_back(_activePlayers[i]);
    }
    return winners;
}


void BlackJack::Initialize()
{
    try
    {
        ReadPlayersFromFile();
    }
    catch (FileNotFoundException)
    {
    	return;
    }
}

void BlackJack::ReadPlayersFromFile()
{
    std::ifstream file (Player::GetPlayersFileName(), std::ios::binary | std::ios::in);

    if (!file.is_open())
        throw FileNotFoundException(Player::GetPlayersFileName(), Player::GetPlayersFileName() + " not found!");

    while (!file.fail())
    {
        Player tempPlayer(file, this);
        _players.push_back(tempPlayer);
        _waitingPlayers.push(&_players.back());
    }

    file.close();
}

void BlackJack::RemovePlayer(Player* player)
{
    for (int i = 0; i < NUM_ACTIVE_PLAYERS; ++i)
    {
        if (_activePlayers[i] == player)
        {
            if (Player* nextPlayer = SelectNextPlayer())
                _activePlayers[i] = nextPlayer; // TODO call some other function signaling that a new player was added
            else
                _activePlayers[i] = NULL; // TODO call a function that will handle the fact that there are no new players

            return;
        }
    }
}

Player* BlackJack::SelectNextPlayer()
{
    if (_waitingPlayers.size() == 0)
        return NULL;

    Player* plr = _waitingPlayers.front();
    _waitingPlayers.pop();

    return plr;
}

bool BlackJack::ShouldEnd()
{
    int activePlayerCount = 0;
    for (int i = 0; i < NUM_ACTIVE_PLAYERS; ++i)
        if (_activePlayers[i] != NULL)
            activePlayerCount++;

    return _waitingPlayers.size() == 0 && activePlayerCount > 1;
}

void BlackJack::VerifyPlayersBalance()
{
    for (int i = 0; i < NUM_ACTIVE_PLAYERS; ++i)
    {
        if (_activePlayers[i] != NULL)
            if (_activePlayers[i]->GetBalance() <= 0.0)
                RemovePlayer(_activePlayers[i]); // this will also select next player
    }
}

bool BlackJack::CanStart()
{
    int activePlayerCount = 0;
    for (int i = 0; i < NUM_ACTIVE_PLAYERS; ++i)
    {
        if (_activePlayers[i] != NULL)
            activePlayerCount++;
    }

    return activePlayerCount > 1;
}
