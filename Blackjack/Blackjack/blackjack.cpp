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

    _activePlayerCount = 0;

    _activePlayers = new Player*[NUM_ACTIVE_PLAYERS];
    for (unsigned int i = 0; i < NUM_ACTIVE_PLAYERS; ++i)
        _activePlayers[i] = NULL;

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
        _activePlayers[i] = SelectNextPlayer();
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

void BlackJack::UnloadContents()
{
    WritePlayersToFile();
}

void BlackJack::ReadPlayersFromFile()
{
    std::ifstream file (Player::GetPlayersFileName(), std::ios::in);

    if (!file.is_open())
        throw FileNotFoundException(Player::GetPlayersFileName(), Player::GetPlayersFileName() + " not found!");

    while (!file.fail() || !file.eof())
    {
        try
        {
            AddPlayer(Player(file, this));
        }
        catch (InvalidPlayerException &e)
        {
        	break;
        }
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

    _activePlayerCount--;
}

Player* BlackJack::SelectNextPlayer()
{
    if (_waitingPlayers.size() == 0)
        return NULL;

    Player* plr = _waitingPlayers.front();
    _waitingPlayers.pop();

    _activePlayerCount++;

    return plr;
}

bool BlackJack::ShouldEnd()
{
    return _waitingPlayers.size() == 0 && _activePlayerCount > 1;
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

void BlackJack::AddPlayer(Player player)
{
    _players.push_back(player);
    _waitingPlayers.push(&_players.back());
}

void BlackJack::WritePlayersToFile()
{
    std::ofstream out (Player::GetPlayersFileName());

    for (std::vector<Player>::const_iterator plr = _players.begin(); plr != _players.end(); ++plr)
    {
        plr->WriteText(out);
        out << '\n';
    }
}
