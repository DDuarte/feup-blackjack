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
#include "sounds.h"

#include <string>
#include <fstream>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

double S_Game::_bet = 5.0;
Stats S_Game::Statistics;

S_Game::S_Game() { }

void S_Game::Initialize()
{
    _players = std::vector<Player>();
    _waitingPlayers = std::queue<Player*>();
    _activePlayers = new Player*[MAX_ACTIVE_PLAYERS];
    _log = new TextLog;
    _deck = new Deck();
    _dealer = new Dealer(this);

    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
        _activePlayers[i] = NULL;

    _activePlayerIndex = 0;
    _gameState = 0;
    _playerPlayed = false;

    _buttons.push_back(new RectButton(Vector2D(95,35), Vector2D(325, 550) , al_map_rgb(70, 4, 4), al_map_rgb(238, 233, 233), al_map_rgb(255, 255, 255), GetStr(STR_HIT),    36, RectButton::ButtonHandler(), true));
    _buttons.push_back(new RectButton(Vector2D(95,35), Vector2D(435, 550) , al_map_rgb(70, 4, 4), al_map_rgb(238, 233, 233), al_map_rgb(255, 255, 255), GetStr(STR_STAND),  36, RectButton::ButtonHandler(), true));
    _buttons.push_back(new RectButton(Vector2D(95,35), Vector2D(540, 550) , al_map_rgb(70, 4, 4), al_map_rgb(238, 233, 233), al_map_rgb(255, 255, 255), GetStr(STR_DOUBLE), 36, RectButton::ButtonHandler(), true));
    _buttons.push_back(new RectButton(Vector2D(205,35), Vector2D(540, 550), al_map_rgb(70, 4, 4), al_map_rgb(238, 233, 233), al_map_rgb(255, 255, 255), GetStr(STR_GIVEUP), 36, RectButton::ButtonHandler(), true));
    _buttons.push_back(new RectButton(Vector2D(205,35), Vector2D(325, 550), al_map_rgb(70, 4, 4), al_map_rgb(238, 233, 233), al_map_rgb(255, 255, 255), GetStr(STR_STAY),   36, RectButton::ButtonHandler(), true));
}

void S_Game::LoadContents()
{
    ReadPlayersFromFile();
    for (std::vector<Player>::iterator plr = _players.begin(); plr != _players.end(); ++plr)
        if (plr->GetBalance() >= _bet)
            _waitingPlayers.push(&(*plr));

    SelectPlayers();
}

void S_Game::UnloadContents()
{
    delete _dealer;
    delete _deck;
    delete _log;
    delete _activePlayers;

    _buttons.clear();
    _players.clear();
    while (!_waitingPlayers.empty()) _waitingPlayers.pop();
}

void S_Game::Draw()
{
    // Draw Background
    static Bitmap bg(BITMAP_GAME_BACKGROUND);
    bg.Draw();

    // Draw buttons
    for (std::vector<RectButton*>::iterator btn = _buttons.begin(); btn != _buttons.end(); ++btn)
        if ((*btn)->Visible) (*btn)->Draw();

    // Draw each player
    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
        if (_activePlayers[i] != NULL)
            _activePlayers[i]->Draw(i == _activePlayerIndex && (_gameState == GAME_STATE_PLAYER_TURN || _gameState == GAME_STATE_STAY_OR_GIVE_UP));

    // Draw dealer
    _dealer->Draw();

    // Draw deck
    _deck->Draw();

    // Draw log text box
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
            return !BlackJack::Instance()->Quit(true);
        }
        case ALLEGRO_EVENT_KEY_UP:
        {
            if (ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                return !BlackJack::Instance()->Quit(true);
            }
            break;
        }
        case ALLEGRO_EVENT_TIMER:
        {
            switch (_gameState)
            {
                case GAME_STATE_PLACING_BETS:
                {
                    if (CountActivePlayers() < MIN_ACTIVE_PLAYERS)
                    {
                        Statistics.Players = _players;
                        Statistics.CalculateWinners();
                        
                        UpdatePlayersFile();

                        for (int i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
                        {
                            if (_activePlayers[i] != NULL)
                            {
                                Statistics.Winner = _activePlayers[i];
                                break;
                            }
                        }

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
                                    PlaySoundOnce(SAMPLE_DEALER_BLACKJACK_SOUND);

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
                    if (_dealer->IsBlackjack())
                    {
                        NextInternalGameState();
                        NextInternalGameState(); // go to check results
                    }

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
    _log->AddString(GetStr(STR_PLAYER_HIT_F).c_str(), player->GetName().c_str(), card->GetName().c_str());

    PlaySoundOnceS(SAMPLE_DEAL_CARD_SOUND, 2.0);

    Statistics.HitCount += 1;

    if (player->HasLost())
    {
        _playerPlayed = true;
        return;
    }

    _playerPlayed = false;
}

void S_Game::PlayerStand(Player* player)
{
    _log->AddString(GetStr(STR_PLAYER_STAND_F).c_str(), player->GetName().c_str());

    _playerPlayed = true;
    Statistics.StandCount += 1;
}

void S_Game::PlayerDouble(Player* player, Card* card)
{
    _log->AddString(GetStr(STR_PLAYER_DOUBLE_F).c_str(), player->GetName().c_str(), card->GetName().c_str());

    PlaySoundOnce(SAMPLE_DOUBLE_SOUND);
    _playerPlayed = true;
    Statistics.DoubleCount += 1;
}

void S_Game::PlayerSurrender(Player* player)
{
    _playerPlayed = true;
}

void S_Game::PlayerStay(Player* player)
{
    _playerPlayed = true;
    Statistics.StandCount += 1;
}

void S_Game::PlayerBet(Player* player)
{
    Statistics.TotalMoneyBetPlayers += _bet;
    Statistics.BetCount += 1;
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
    if (_waitingPlayers.size() < MIN_ACTIVE_PLAYERS)
    {
        al_show_native_message_box(BlackJack::Instance()->GetDisplay(), "Error", "", "Not enough players to start a game. Fill in players.txt.", 0, ALLEGRO_MESSAGEBOX_ERROR);
        BlackJack::Instance()->Quit();
        return;
    }

    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
    {
        Player* player = SelectNextPlayerFromQueue();
        if (!player) break;

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
    al_stop_samples();
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
            PlaySoundOnceS(SAMPLE_DEAL_CARD_SOUND, 2.0);
        }
    }
    else
    {
        _dealer->NewCard(_deck->WithdrawCard());
        PlaySoundOnceS(SAMPLE_DEAL_CARD_SOUND, 2.0);
    }

    return false;
}

bool S_Game::HandleStatePlayerTurn()
{
    if (_activePlayerIndex >= MAX_ACTIVE_PLAYERS)
        return false;

    if (_activePlayers[_activePlayerIndex] == NULL)
        return true;

    if (_activePlayers[_activePlayerIndex]->IsBlackjack())
    {
        _buttons[BUTTON_HIT]->Visible = false;
        _buttons[BUTTON_STAND]->Visible = false;
        _playerPlayed = true;
        return true;
    }

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
        PlaySoundOnceS(SAMPLE_DEAL_CARD_SOUND, 2.0);
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
            if (_activePlayers[i]->IsBlackjack())
                Statistics.BlackjackCount += 1;
            else if (_activePlayers[i]->IsBusted())
                Statistics.BustedCount += 1;

            double money = 0.0;

            if (_activePlayers[i]->IsBusted())
                ;
            else if (_dealer->IsBusted()) // assumes player did NOT bust
                money = 2*(S_Game::GetBet() * (1 + _activePlayers[i]->IsDoubleBet()));
            else if (_activePlayers[i]->IsBlackjack() && !_dealer->IsBlackjack())
                money = 3*(S_Game::GetBet() * (1 + _activePlayers[i]->IsDoubleBet()));
            else if (_activePlayers[i]->GetScore() >= _dealer->GetScore())
                money = 1*(S_Game::GetBet() * (1 + _activePlayers[i]->IsDoubleBet()));

            _activePlayers[i]->IncreaseBalance(money);
            Statistics.TotalMoneyReceivedPlayers += money;
        }
    }

    Statistics.RoundCount += 1;

    return true;
}

bool S_Game::HandleStateStayOrGiveUp()
{
    if (_activePlayerIndex >= MAX_ACTIVE_PLAYERS)
        return false;

    if (_activePlayers[_activePlayerIndex] == NULL)
        return true;

    if (_activePlayers[_activePlayerIndex]->GetBalance() >= _bet)
    {
        _buttons[BUTTON_GIVE_UP]->Handler()->Bind<Player, &Player::Surrender>(_activePlayers[_activePlayerIndex]);
        _buttons[BUTTON_STAY_GAME]->Handler()->Bind<Player, &Player::Stay>(_activePlayers[_activePlayerIndex]);
        _buttons[BUTTON_GIVE_UP]->Visible = true;
        _buttons[BUTTON_STAY_GAME]->Visible = true;
    }
    else
        _playerPlayed = true; // will be replaced next round

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
            if (_activePlayers[i]->GetBalance() < _bet || _activePlayers[i]->WantsSurrender())
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
    _log->AddString(GetStr(STR_DEALER_HIT_F).c_str(), card->GetName().c_str());
}

int S_Game::CountActivePlayers() const
{
    int count = 0;
    for (uint i = 0; i < MAX_ACTIVE_PLAYERS; ++i)
        if (_activePlayers[i] != NULL)
            count++;

    return count;
}

void S_Game::UpdatePlayersFile() const
{
    std::ofstream out(Player::GetPlayersFileName());

    if (!out.is_open())
        Error("Error creating players.txt file");

    out << _players.cbegin()->GetBalance() << " " << _players.cbegin()->GetName();
    for (std::vector<Player>::const_iterator p = _players.cbegin()+1; p != _players.cend(); p++)
    {
        out << std::endl << p->GetBalance() << " " << p->GetName();
    }

}
