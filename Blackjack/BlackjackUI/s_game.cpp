#include "deck.h"
#include "s_game.h"
#include "card.h"
#include "blackjack.h"
#include "hand.h"
#include "fonts.h"
#include "dealer.h"
#include "player.h"
#include "game_exceptions.h"
#include "rect_button.h"
#include "localization.h"
#include "text_log.h"
#include "bitmaps.h"

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

    _dealCardSound = NULL;
    _doubleSound = NULL;
    _dealerBlackjackSound = NULL;

    _activePlayerIndex = -1;
    _gameState = -1;
    _dealer = NULL;
    _playerPlayed = false;

    _log = new TextLog;
}

void S_Game::Initialize()
{
    _deck = new Deck();
    _dealer = new Dealer(this);

    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
        _activePlayers[i] = NULL;

    _buttons.push_back(new RectButton(Vector2D(95,35), Vector2D(325, 550) , al_map_rgb(70, 4, 4), al_map_rgb(238, 233, 233), al_map_rgb(255, 255, 255), GetStr(STR_HIT),    36, RectButton::ButtonHandler(), true));
    _buttons.push_back(new RectButton(Vector2D(95,35), Vector2D(435, 550) , al_map_rgb(70, 4, 4), al_map_rgb(238, 233, 233), al_map_rgb(255, 255, 255), GetStr(STR_STAND),  36, RectButton::ButtonHandler(), true));
    _buttons.push_back(new RectButton(Vector2D(95,35), Vector2D(540, 550) , al_map_rgb(70, 4, 4), al_map_rgb(238, 233, 233), al_map_rgb(255, 255, 255), GetStr(STR_DOUBLE), 36, RectButton::ButtonHandler(), true));
    _buttons.push_back(new RectButton(Vector2D(205,35), Vector2D(540, 550), al_map_rgb(70, 4, 4), al_map_rgb(238, 233, 233), al_map_rgb(255, 255, 255), GetStr(STR_GIVEUP), 36, RectButton::ButtonHandler(), true));
    _buttons.push_back(new RectButton(Vector2D(205,35), Vector2D(325, 550), al_map_rgb(70, 4, 4), al_map_rgb(238, 233, 233), al_map_rgb(255, 255, 255), GetStr(STR_STAY),   36, RectButton::ButtonHandler(), true));
}

void S_Game::LoadContents()
{
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

void S_Game::UnloadContents()
{
    al_destroy_sample(_dealCardSound);
    al_destroy_sample(_doubleSound);
    al_destroy_sample(_dealerBlackjackSound);

    delete _dealer;
    delete _deck;
    delete _log;

    Card::DestroyBitmaps();
}

void S_Game::Draw()
{
    // Draw Background
    Bitmap(BITMAP_GAME_BACKGROUND).Draw();

    for (std::vector<RectButton*>::iterator btn = _buttons.begin(); btn != _buttons.end(); ++btn)
        if ((*btn)->Visible) (*btn)->Draw();

    // Debug printing
    al_draw_textf(Fonts::GetFont(10), al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "x: %3.1f y: %3.1f", BlackJack::GetMousePosition().X, BlackJack::GetMousePosition().Y);

    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
        if (_activePlayers[i] != NULL)
            _activePlayers[i]->Draw(i == _activePlayerIndex && (_gameState == GAME_STATE_PLAYER_TURN || _gameState == GAME_STATE_STAY_OR_GIVE_UP));

    _dealer->Draw();
    _deck->Draw();
    _log->Draw();
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
                if ((*btn)->Visible) (*btn)->Update(ev);
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
                int result = al_show_native_message_box(BlackJack::Instance()->GetDisplay(), "Sair", "", "Deseja sair?", NULL, ALLEGRO_MESSAGEBOX_QUESTION|ALLEGRO_MESSAGEBOX_OK_CANCEL);
                if (result == 2 || result == 0)
                    return true;
                else
                {
                    BlackJack::Instance()->Quit();
                    return false;
                }
            }
            break;
        }
        case ALLEGRO_EVENT_TIMER:
        {
            switch (_gameState)
            {
                case GAME_STATE_PLACING_BETS:
                {
                    if (CountActivePlayers() <= 1)
                    {
                        BlackJack::Instance()->ChangeState(STATE_GAME_OVER);
                        return true;
                    }

                    while (!HandleStatePlacingBets()) ;
                    break;
                }
                case GAME_STATE_DEALING_CARDS:
                {
                    for (std::vector<RectButton*>::iterator btn = _buttons.begin(); btn != _buttons.end(); ++btn)
                        (*btn)->Visible = false;

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
                                    al_play_sample(_dealerBlackjackSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

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
                    for (std::vector<RectButton*>::iterator btn = _buttons.begin(); btn != _buttons.end(); ++btn)
                        (*btn)->Visible = true;

                    if (HandleStatePlayerTurn())
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
                    for (std::vector<RectButton*>::iterator btn = _buttons.begin(); btn != _buttons.end(); ++btn)
                        (*btn)->Visible = false;
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
                case GAME_STATE_STAY_OR_GIVE_UP:
                {
                    if (HandleStateStayOrGiveUp())
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
                case GAME_STATE_POST_GAME:
                    while (!HandleStatePostGame()) ;
                    break;
                case GAME_STATE_RESET_ROUND:
                    while (!HandleStateResetRound()) ;
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

void S_Game::PlayerHit(Player* player, Card* card)
{
    _log->AddString("Jogador: %s | Acção: pedir | Carta %s", player->GetName().c_str(), card->GetName().c_str());

    al_play_sample(_dealCardSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

    if (player->HasLost())
    {
        _playerPlayed = true;
        return;
    }

    _playerPlayed = false;
}

void S_Game::PlayerStand(Player* player)
{
    _log->AddString("Jogador: %s | Acção: ficar", player->GetName().c_str());

    _playerPlayed = true;
}


void S_Game::PlayerDouble(Player* player, Card* card)
{
    _log->AddString("Jogador: %s | Acção: dobrar | Carta %s", player->GetName().c_str(), card->GetName().c_str());

    al_play_sample(_doubleSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    _playerPlayed = true;
}

void S_Game::PlayerSurrender(Player* player)
{
    _playerPlayed = true;
}

void S_Game::PlayerStay(Player* player)
{
    _playerPlayed = true;
}

void S_Game::PlayerBet(Player* player)
{

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
    if (_waitingPlayers.size() <= 1)
        throw InvalidPlayerException("Not enough players to start a game."); 

    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
    {
        Player* player = SelectNextPlayerFromQueue();
        if (player == NULL)
            break;

        _activePlayers[i] = player;
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
    if (_gameState > GAME_STATE_RESET_ROUND)
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
    if (_activePlayerIndex >= MAX_ACTIVE_PLAYERS)
        return false;

    if (_activePlayers[_activePlayerIndex] == NULL)
        return true;

    _buttons[BUTTON_HIT]->Handler()->Bind<Player, &Player::Hit>(_activePlayers[_activePlayerIndex]);
    _buttons[BUTTON_STAND]->Handler()->Bind<Player, &Player::Stand>(_activePlayers[_activePlayerIndex]);
    _buttons[BUTTON_DOUBLE]->Handler()->Bind<Player, &Player::Double>(_activePlayers[_activePlayerIndex]);

    if (!_activePlayers[_activePlayerIndex]->CanDouble())
        _buttons[BUTTON_DOUBLE]->Visible = false;

    _buttons[BUTTON_GIVE_UP]->Visible = false;
    _buttons[BUTTON_STAY_GAME]->Visible = false;

    return _playerPlayed;
}

bool S_Game::HandleStateDealerTurn()
{
    _dealer->ShowSecondCard();
    if (_dealer->GetScore() < 17)
    {
        _dealer->Hit();
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

bool S_Game::HandleStateStayOrGiveUp()
{
    if (_activePlayerIndex >= MAX_ACTIVE_PLAYERS)
        return false;

    if (_activePlayers[_activePlayerIndex] == NULL)
        return true;

    _buttons[BUTTON_GIVE_UP]->Handler()->Bind<Player, &Player::Surrender>(_activePlayers[_activePlayerIndex]);
    _buttons[BUTTON_STAY_GAME]->Handler()->Bind<Player, &Player::Stay>(_activePlayers[_activePlayerIndex]);

    _buttons[BUTTON_GIVE_UP]->Visible = true;
    _buttons[BUTTON_STAY_GAME]->Visible = true;

    return _playerPlayed;
}

bool S_Game::HandleStateResetRound()
{
    _buttons[BUTTON_GIVE_UP]->Visible = false;
    _buttons[BUTTON_STAY_GAME]->Visible = false;

    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
        if (_activePlayers[i] != NULL)
            _activePlayers[i]->ResetPlayer();

    _dealer->ClearHand();
    _dealer->NoShowSecondCard();

    _deck->ReInitializeDeck();

    _playerPlayed = false;

    return true;
}

bool S_Game::HandleStatePostGame()
{
    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
    {
        if (_activePlayers[i] != NULL)
        {
            if (_activePlayers[i]->GetBalance() <= _bet || _activePlayers[i]->WantsSurrender())
            {
                _activePlayers[i] = SelectNextPlayerFromQueue();
                if (_activePlayers[i] != NULL)
                    _activePlayers[i]->EnterGame(i);
            }
        }
    }

    return true;
}

void S_Game::DealerHit(Dealer* dealer, Card* card)
{
    _log->AddString("Dealer | Acção: pedir | Carta %s", card->GetName().c_str());
}

int S_Game::CountActivePlayers() const
{
    int count = 0;
    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
        if (_activePlayers[_activePlayerIndex] != NULL)
            count++;
    return count;
}
