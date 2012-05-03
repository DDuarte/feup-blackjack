#include "deck.h"
#include "s_game.h"
#include "card.h"
#include "blackjack.h"
#include "hand.h"
#include "fonts.h"
#include "dealer.h"
#include "player.h"
#include "gameExceptions.h"
#include "rectButton.h"
#include "localization.h"

#include <string>
#include <Windows.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

Player** S_Game::_activePlayers = new Player*[MAX_ACTIVE_PLAYERS];
int S_Game::_activePlayerIndex = -1;
double S_Game::_bet = 5.0;

S_Game::S_Game()
{
    _players = std::vector<Player>();
    _waitingPlayers = std::queue<Player*>();

    _background = NULL;
    _dealer = new Dealer(this);
    _gameState = -1;
    _activePlayerCount = 0;

    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
        _activePlayers[i] = NULL;

    _activePlayerIndex = 0;

    _chip = NULL;
}

void S_Game::Initialize()
{
    _deck = new Deck();
}

void S_Game::LoadContents()
{
    _background = al_load_bitmap("../../Resources/playing_table.png");
    _chip = al_load_bitmap("../../Resources/chip1.png");

    ReadPlayersFromFile();
    for (std::vector<Player>::iterator plr = _players.begin(); plr != _players.end(); ++plr)
        _waitingPlayers.push(&(*plr));
    SelectPlayers();
    _gameState = 0;
}

void S_Game::Draw()
{
    // Draw Background
    al_draw_bitmap(_background, 0, 0, 0);

    for (std::vector<RectButton*>::iterator btn = _buttons.begin(); btn != _buttons.end(); ++btn)
        (*btn)->Draw();

    // Debug printing
    al_draw_textf(Fonts::GetFont(10), al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "x: %3.1f y: %3.1f", BlackJack::GetMousePosition().X, BlackJack::GetMousePosition().Y);

    for (int i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
    {
        if (_activePlayers[i] != NULL)
            _activePlayers[i]->Draw(i==_activePlayerIndex && _gameState == GAME_STATE_PLAYER_TURN);
    }

    _dealer->Draw();

    _deck->Draw();
}

void S_Game::UnloadContents()
{
    al_destroy_bitmap(_background);
    al_destroy_bitmap(_chip);

    delete _dealer;
    Card::DestroyBitmaps();
}

bool S_Game::Update(ALLEGRO_EVENT* ev)
{
    if (!ev)
        return false;

    for (std::vector<RectButton*>::iterator btn = _buttons.begin(); btn != _buttons.end(); ++btn)
    {
        int temp = _activePlayerIndex;
        (*btn)->Update(ev);
        if (_activePlayerIndex != temp)
            break;
    }

    switch (ev->type)
    {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        {
            BlackJack::Instance()->Quit();
            return false;
        }
    case ALLEGRO_EVENT_KEY_UP:
        {
            if (ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                BlackJack::Instance()->Quit();
                return false;
            }
            break;
        }
    case ALLEGRO_EVENT_TIMER:
        {
            if (_activePlayers[0] != NULL && !_activePlayers[0]->IsPositionSet()) _activePlayers[0]->SetPosition(Vector2D(652, 217));
            if (_activePlayers[1] != NULL && !_activePlayers[1]->IsPositionSet()) _activePlayers[1]->SetPosition(Vector2D(460, 344));
            if (_activePlayers[2] != NULL && !_activePlayers[2]->IsPositionSet()) _activePlayers[2]->SetPosition(Vector2D(260, 344));
            if (_activePlayers[3] != NULL && !_activePlayers[3]->IsPositionSet()) _activePlayers[3]->SetPosition(Vector2D(82, 217));

            switch (_gameState)
            {
            case GAME_STATE_PLACING_BETS:
                return HandleStatePlacingBets();
            case GAME_STATE_DEALING_CARDS:
                return HandleStateDealingCards();
            case GAME_STATE_PLAYER_TURN:
                return HandleStatePlayerTurn();
            case GAME_STATE_DEALER_TURN:
                return HandleStateDealerTurn();
            case GAME_STATE_CHECK_RESULTS:
                return HandleStateCheckResults();
            case GAME_STATE_RESET_ROUND:
                return HandleStateResetRound();
            case GAME_STATE_POST_GAME:
                return HandleStatePostGame();
            default:
                return false;
            }
        }
    }

    return false;
}

void S_Game::PlayerHit(Player* player)
{

    if (player->HasLost())
    {
        NextPlayer();
        _buttons.erase(_buttons.begin(), _buttons.end());
        //al_show_native_message_box(BlackJack::Instance()->GetDisplay(), "Bust","Hit","Hit","ok",0 );
        //player->Lose();
    }
}

void S_Game::PlayerStand( Player* player )
{
    NextPlayer();
    _buttons.erase(_buttons.begin(), _buttons.end());
}


void S_Game::PlayerDouble( Player* player )
{
    PlayerStand(player);
}

void S_Game::ReadPlayersFromFile()
{
    std::ifstream file(Player::GetPlayersFileName(), std::ios::in);

    if (!file.is_open())
        throw FileNotFoundException(Player::GetPlayersFileName(), Player::GetPlayersFileName() + " not found!");

    while (!file.fail() || !file.eof())
    {
        try
        {
            _players.push_back(Player(file, const_cast<S_Game*>(this)));
        }
        catch (InvalidPlayerException)
        {
            break;
        }
    }

    file.close();
}

void S_Game::SelectPlayers()
{
    if (_waitingPlayers.empty() || _waitingPlayers.size() < MAX_ACTIVE_PLAYERS)
        throw InvalidPlayerException("Not enough players to start a game."); 

    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
        _activePlayers[i] = SelectNextPlayerFromQueue();
}

Player* S_Game::SelectNextPlayerFromQueue()
{
    if (_waitingPlayers.size() == 0)
        return NULL;

    Player* plr = _waitingPlayers.front();
    _waitingPlayers.pop();

    _activePlayerCount++;

    return plr;
}

void S_Game::NextPlayer()
{
    _activePlayerIndex++;
    if (_activePlayerIndex >= MAX_ACTIVE_PLAYERS)
        NextInternalGameState();
}

void S_Game::NextInternalGameState()
{
    _gameState++;
    _activePlayerIndex = 0;
    _tempCounter = 0;
    if (_gameState > GAME_STATE_POST_GAME)
        _gameState = 0;
}

bool S_Game::HandleStatePlacingBets()
{
    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; i++)
        if (_activePlayers[i] != NULL)
            _activePlayers[i]->PlaceBet();

    NextInternalGameState();
    return true;
}

bool S_Game::HandleStateDealingCards()
{
    static bool dealerDealingTurn = true;

    if (_tempCounter == 20)
    {
        _tempCounter = 0;
        if (dealerDealingTurn)
        {
            dealerDealingTurn = false;
            _dealer->AddNewCard(_deck->WithdrawCard());
        }
        else
        {
            _activePlayers[_activePlayerIndex]->NewCard(_deck->WithdrawCard());
            _activePlayerIndex++;
            if (_activePlayerIndex >= MAX_ACTIVE_PLAYERS)
            {
                _activePlayerIndex = 0;
                if (_dealer->GetHand()->GetNumberOfCards() < 2)
                    dealerDealingTurn = true;
                else
                    NextInternalGameState();
            }
        }
        _tempCounter++;

    }
    else
        _tempCounter++;

    return true;
}

bool S_Game::HandleStatePlayerTurn()
{
    if (_buttons.size() == 0 )
    {
        _buttons.push_back(new RectButton(Vector2D(50,50), Vector2D(300, 500), al_map_rgb(255, 255, 255), al_map_rgb(238, 233, 233), al_map_rgb(0, 0, 0), GetStr(STR_HIT), 20, RectButton::ButtonHandler().Bind<Player, &Player::Hit>(_activePlayers[_activePlayerIndex]), true));
        _buttons.push_back(new RectButton(Vector2D(50,50), Vector2D(410, 500), al_map_rgb(255, 255, 255), al_map_rgb(238, 233, 233), al_map_rgb(0, 0, 0), GetStr(STR_STAND), 20, RectButton::ButtonHandler().Bind<Player, &Player::Stand>(_activePlayers[_activePlayerIndex]), true));
        _buttons.push_back(new RectButton(Vector2D(50,50), Vector2D(520, 500), al_map_rgb(255, 255, 255), al_map_rgb(238, 233, 233), al_map_rgb(0, 0, 0), GetStr(STR_DOUBLE), 20, RectButton::ButtonHandler().Bind<Player, &Player::Double>(_activePlayers[_activePlayerIndex]), true));

        //_buttons.push_back(new RectButton(Vector2D(50,100),Vector2D(630, 500),al_map_rgb(255,255,255),al_map_rgb(0,0,0), GetStr(STR_GIVEUP), 20, &HandleButtonClick , true));
        //_buttons.push_back(new RectButton(Vector2D(50, 440), al_map_rgb(200, 200, 200), "Hit", 50, &HandleButtonClick, true));
    }

    return true;
}

bool S_Game::HandleStateDealerTurn()
{
    static uint tempCounter = 0;
    _dealer->ShowSecondCard();
    if (tempCounter == 20)
    {
        tempCounter = 0;
        if (_dealer->GetHand()->GetScore() < 17)
            _dealer->AddNewCard(_deck->WithdrawCard());
        else
            NextInternalGameState();
        tempCounter++;
    }
    else
        tempCounter++;

    return true;
}

bool S_Game::HandleStateCheckResults()
{
    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; i++)
    {
        if (_activePlayers[i] != NULL)
        {
            if (_activePlayers[i]->IsBusted())
                _activePlayers[i]->Lose();
            else if (_dealer->IsBusted()) // assumes player did NOT bust
                _activePlayers[i]->DealerBusts();
            else if (_activePlayers[i]->IsBlackjack() && !_dealer->IsBlackjack())
                _activePlayers[i]->WinsItAll();
            else if (_activePlayers[i]->GetHand()->GetScore() >= _dealer->GetHand()->GetScore())
                _activePlayers[i]->Wins();
        }
    }

    NextInternalGameState();
    return true;
}

bool S_Game::HandleStateResetRound()
{
    if (false)
    {
        for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
            _activePlayers[i]->ResetPlayer();

        _dealer->ClearHand();

        delete _deck;
        _deck = new Deck();

        _gameState = GAME_STATE_PLACING_BETS;

        _activePlayerIndex = 0;
    }

    return true;
}
