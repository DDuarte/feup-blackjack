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

double S_Game::_bet = 5.0;

S_Game::S_Game()
{
    _players = std::vector<Player>();
    _waitingPlayers = std::queue<Player*>();
    _activePlayers = new Player*[MAX_ACTIVE_PLAYERS];

    _background = NULL;
    _chip = NULL;
    _dealCardSound = NULL;
    _doubleSound = NULL;
    _dealerBlackjackSound = NULL;

    _activePlayerIndex = -1;
    _gameState = -1;
    _dealer = NULL;
    _playerPlayed = false;
}

void S_Game::Initialize()
{
    _deck = new Deck();
    _dealer = new Dealer(this);

    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
        _activePlayers[i] = NULL;

    _buttons.push_back(new RectButton(Vector2D(50,50), Vector2D(300, 500), al_map_rgb(255, 255, 255), al_map_rgb(238, 233, 233), al_map_rgb(0, 0, 0), GetStr(STR_HIT), 20, RectButton::ButtonHandler().Bind<Player, &Player::Hit>(_activePlayers[_activePlayerIndex]), true));
    _buttons.push_back(new RectButton(Vector2D(50,50), Vector2D(410, 500), al_map_rgb(255, 255, 255), al_map_rgb(238, 233, 233), al_map_rgb(0, 0, 0), GetStr(STR_STAND), 20, RectButton::ButtonHandler().Bind<Player, &Player::Stand>(_activePlayers[_activePlayerIndex]), true));
    _buttons.push_back(new RectButton(Vector2D(50,50), Vector2D(520, 500), al_map_rgb(255, 255, 255), al_map_rgb(238, 233, 233), al_map_rgb(0, 0, 0), GetStr(STR_DOUBLE), 20, RectButton::ButtonHandler().Bind<Player, &Player::Double>(_activePlayers[_activePlayerIndex]), true));
    //_buttons.push_back(new RectButton(Vector2D(50,100),Vector2D(630, 500),al_map_rgb(255,255,255),al_map_rgb(0,0,0), GetStr(STR_GIVEUP), 20, &HandleButtonClick , true));
    //_buttons.push_back(new RectButton(Vector2D(50, 440), al_map_rgb(200, 200, 200), "Hit", 50, &HandleButtonClick, true));
}

void S_Game::LoadContents()
{
    _background = al_load_bitmap("../../Resources/playing_table.png");
    _chip = al_load_bitmap("../../Resources/chip1.png");
    _dealCardSound = al_load_sample("../../Resources/sounds/86854__milton__cardfall.ogg");
    _doubleSound = al_load_sample("../../Resources/sounds/86859__milton__double.ogg");
    _dealerBlackjackSound = al_load_sample("../../Resources/sounds/86857__milton__dealerblackjack.ogg");

    ReadPlayersFromFile();
    for (std::vector<Player>::iterator plr = _players.begin(); plr != _players.end(); ++plr)
        _waitingPlayers.push(&(*plr));

    SelectPlayers();
    _activePlayerIndex = 0;
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
            _activePlayers[i]->Draw(i == _activePlayerIndex && _gameState == GAME_STATE_PLAYER_TURN);
    }

    _dealer->Draw();
    _deck->Draw();
}

void S_Game::UnloadContents()
{
    al_destroy_bitmap(_background);
    al_destroy_bitmap(_chip);
    al_destroy_sample(_dealCardSound);
    al_destroy_sample(_doubleSound);
    al_destroy_sample(_dealerBlackjackSound);

    delete _dealer;
    delete _deck;

    Card::DestroyBitmaps();
}

bool S_Game::Update(ALLEGRO_EVENT* ev)
{
    if (!ev)
        return false;

    switch (ev->type)
    {
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        {
            for (std::vector<RectButton*>::iterator btn = _buttons.begin(); btn != _buttons.end(); ++btn)
                (*btn)->Update(ev);
            return false;
        }
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
            switch (_gameState)
            {
                case GAME_STATE_PLACING_BETS:
                    while (!HandleStatePlacingBets()) ;
                    break;
                case GAME_STATE_DEALING_CARDS:
                {
                    static int timer = 10;
                    if (!timer)
                    {
                        timer = 10;
                        static uint counter = 0;
                        if (HandleStateDealingCards(counter++))
                        {
                            static uint counter2 = 0;
                            if (HandleStateDealingCards(counter2++))
                            {
                                counter = 0;
                                counter2 = 0;

                                if (_dealer->IsBlackjack())
                                {
                                    al_play_sample(_dealerBlackjackSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                }
                                break;
                            }
                        }
                        return true;
                    }
                    else
                        --timer;

                    return true;
                }
                case GAME_STATE_PLAYER_TURN:
                {
                    HandleStatePlayerTurn();

                    if (_playerPlayed)
                    {
                            _activePlayerIndex++;
                            _playerPlayed = false;
                            return true;
                    }

                    if (_activePlayerIndex >= MAX_ACTIVE_PLAYERS)
                    {
                        _activePlayerIndex = 0;
                        break;
                    }

                    return true;
                }
                case GAME_STATE_DEALER_TURN:
                {
                    static int timer = 15;
                    if (!timer)
                    {
                        timer = 15;
                        if (HandleStateDealerTurn())
                            break;
                    }
                    
                    timer--;
                    return true;
                }
                case GAME_STATE_CHECK_RESULTS:
                    while (!HandleStateCheckResults()) ;
                    break;
                case GAME_STATE_RESET_ROUND:
                    while (!HandleStateResetRound()) ;
                    break;
                case GAME_STATE_POST_GAME:
                    while (!HandleStatePostGame()) ;
                    break;
                default:
                    return false;
            }

            NextInternalGameState();
            return true;
        }
    }

    return false;
}

void S_Game::PlayerHit(Player* player)
{
    al_play_sample(_dealCardSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

    if (player->HasLost())
    {
        _playerPlayed = true;
        return;
    }

    _playerPlayed = false;
}

void S_Game::PlayerStand( Player* player )
{
    _playerPlayed = true;
}


void S_Game::PlayerDouble( Player* player )
{
    al_play_sample(_doubleSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    _playerPlayed = true;
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
            _players.push_back(Player(file, this));
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
    {
        _activePlayers[i] = SelectNextPlayerFromQueue();
        _activePlayers[i]->EnterGame(i);
    }
}

Player* S_Game::SelectNextPlayerFromQueue()
{
    if (_waitingPlayers.size() == 0)
        return NULL;

    Player* plr = _waitingPlayers.front();
    _waitingPlayers.pop();

    return plr;
}

void S_Game::NextInternalGameState()
{
    _gameState++;
    _activePlayerIndex = 0;
    if (_gameState > GAME_STATE_POST_GAME)
        _gameState = GAME_STATE_PLACING_BETS;
}

bool S_Game::HandleStatePlacingBets()
{
    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; i++)
        if (_activePlayers[i] != NULL)
            _activePlayers[i]->PlaceBet();

    return true;
}

bool S_Game::HandleStateDealingCards(uint i)
{
    if (i >= MAX_ACTIVE_PLAYERS + 1)
        return true;

    if (i < MAX_ACTIVE_PLAYERS)
    {
        if (_activePlayers[i] != NULL)
        {
            _activePlayers[i]->NewCard(_deck->WithdrawCard());
            al_play_sample(_dealCardSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
    }
    else
    {
        _dealer->NewCard(_deck->WithdrawCard());
        al_play_sample(_dealCardSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }

    return false;
}

bool S_Game::HandleStatePlayerTurn()
{
    _buttons[0]->Handler()->Bind<Player, &Player::Hit>(_activePlayers[_activePlayerIndex]);
    _buttons[1]->Handler()->Bind<Player, &Player::Stand>(_activePlayers[_activePlayerIndex]);
    _buttons[2]->Handler()->Bind<Player, &Player::Double>(_activePlayers[_activePlayerIndex]);

    return _playerPlayed;
}

bool S_Game::HandleStateDealerTurn()
{
    _dealer->ShowSecondCard();
    if (_dealer->GetScore() < 17)
    {
        _dealer->NewCard(_deck->WithdrawCard());
        al_play_sample(_dealCardSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        return false;
    }

    return true;
}

bool S_Game::HandleStateCheckResults()
{
    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; i++)
    {
        if (_activePlayers[i] != NULL)
        {
            if (_activePlayers[i]->IsBusted())
                ;//_activePlayers[i]->Lose();
            else if (_dealer->IsBusted()) // assumes player did NOT bust
                _activePlayers[i]->DealerBusts();
            else if (_activePlayers[i]->IsBlackjack() && !_dealer->IsBlackjack())
                _activePlayers[i]->WinsItAll();
            else if (_activePlayers[i]->GetScore() >= _dealer->GetScore())
                _activePlayers[i]->Wins();
        }
    }

    return true;
}

bool S_Game::HandleStateResetRound()
{
    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
        if (_activePlayers[i] != NULL)
            _activePlayers[i]->ResetPlayer();

    _dealer->ClearHand();

    _deck->ReInitializeDeck();

    _playerPlayed = false;

    return true;
}

bool S_Game::HandleStatePostGame()
{
    // Show surrender button

    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
    {
        if (_activePlayers[i] != NULL)
        {
            if (_activePlayers[i]->GetBalance() <= _bet)
            {
                _activePlayers[i] = this->SelectNextPlayerFromQueue();
                _activePlayers[i]->EnterGame(i);
            }
        }
    }

    return true;
}
