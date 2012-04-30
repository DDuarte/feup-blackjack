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

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

Player** S_Game::_activePlayers = new Player*[NUM_ACTIVE_PLAYERS];
int S_Game::_activePlayerIndex = -1;

bool HandleButtonClick(RectButton* btn);

S_Game::S_Game()
{
    _players = std::vector<Player>();
    _waitingPlayers = std::queue<Player*>();

    _background = NULL;
    _dealer = new Dealer(this);
    _gameState = -1;
    _activePlayerCount = 0;

    for (uint i = 0; i < NUM_ACTIVE_PLAYERS; ++i)
        _activePlayers[i] = NULL;
    
}

void S_Game::Initialize()
{
    _deck = new Deck();
}

void S_Game::LoadContents()
{
    _background = al_load_bitmap("../../Resources/playing_table.png");
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

    if (_activePlayers[0] != NULL) _activePlayers[0]->Draw(Vector2D(652, 217));
    if (_activePlayers[1] != NULL) _activePlayers[1]->Draw(Vector2D(517, 344));
    if (_activePlayers[2] != NULL) _activePlayers[2]->Draw(Vector2D(260, 344));
    if (_activePlayers[3] != NULL) _activePlayers[3]->Draw(Vector2D(82, 217));
    
    // _dealer->Draw(265, 63);
}

void S_Game::UnloadContents()
{
    al_destroy_bitmap(_background);

    delete _dealer;
    Card::DestroyBitmaps();
}

bool S_Game::Update(ALLEGRO_EVENT* ev)
{
    if (!ev)
        return false;

    for (std::vector<RectButton*>::iterator btn = _buttons.begin(); btn != _buttons.end(); ++btn)
        (*btn)->Update(ev);

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
            switch (_gameState)
            {
                case GAME_STATE_PLACING_BETS:
                    _activePlayerIndex = 0;
                    return HandleStatePlacingBets();
                case GAME_STATE_DEALING_CARDS:
                    _activePlayerIndex = 0;
                    return HandleStateDealingCards();
                case GAME_STATE_PLAYER_TURN:
                    _activePlayerIndex = 0;
                    return HandleStatePlayerTurn();
                case GAME_STATE_DEALER_TURN:
                    return HandleStateDealerTurn();
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
    if (player->IsBusted())
    {
        //al_show_native_message_box(BlackJack::Instance()->GetDisplay(), "Bust","Hit","Hit","ok",0 );
        player->Lose();
    }
}

bool S_Game::HandleStatePlacingBets()
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

bool S_Game::HandleStateResetRound()
{

    for (uint i = 0; i < NUM_ACTIVE_PLAYERS; ++i)
        _activePlayers[i]->ResetPlayer();

    _dealer->ClearHand();

    delete _deck;
    _deck = new Deck();

    _gameState = GAME_STATE_PLACING_BETS;

    _activePlayerIndex = 0;

    return true;
}

void S_Game::ReadPlayersFromFile()
{
    std::ifstream file (Player::GetPlayersFileName(), std::ios::in);

    if (!file.is_open())
        throw FileNotFoundException(Player::GetPlayersFileName(), Player::GetPlayersFileName() + " not found!");

    while (!file.fail() || !file.eof())
    {
        try
        {
            _players.push_back(Player(file,const_cast<S_Game*>(this)));
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
    if (_waitingPlayers.empty() || _waitingPlayers.size() < NUM_ACTIVE_PLAYERS)
        throw InvalidPlayerException("Not enough players to start a game."); 

    for (uint i = 0; i < NUM_ACTIVE_PLAYERS; ++i)
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
