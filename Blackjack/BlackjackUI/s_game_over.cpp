#include "s_game_over.h"
#include "bitmap.h"
#include "blackjack.h"
#include "s_game.h"
#include "utilities.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define Stats S_Game::Statistics

bool S_GameOver::Update(ALLEGRO_EVENT* ev)
{
    return true;
}

void S_GameOver::Draw()
{
    static Bitmap bg (BITMAP_MENU_GAME_OVER);
    bg.Draw();

    // Debug printing
    al_draw_textf(Fonts::GetFont(10), al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "x: %3.1f y: %3.1f", BlackJack::GetMousePosition().X, BlackJack::GetMousePosition().Y);

    // outer transparent rectangle
    al_draw_filled_rounded_rectangle(40, 119, 760, 495, 10, 10, al_map_rgba(0, 0, 0, 175));

    

    /*
    double TotalMoneyBetPlayers;
    double TotalMoneyReceivedPlayers;

    int BlackjackCount; v
    int BustedCount;    v
    int DoubleCount;    v
    int HitCount;       v
    int BetCount;       v
    int StandCount;     v
    int RoundCount;     v

    std::vector<Player> Players;
    Player* Winner;
    Player* PlayerWonMoreMoney;
    Player* PlayerLostMoreMoney;
    */

    const int spacing = 25;
    const int x3 = 400;
    int y = 119;

    // First column

    std::pair<const char*, std::string> column1[] =
    {
        std::make_pair("O vencedor é...", Stats.Winner ? Stats.Winner->GetName() : "N/A"),
        std::make_pair("Apostas:", ToString(Stats.BetCount)),
        std::make_pair("Apostas:", ToString(Stats.BetCount)),
        std::make_pair("Rondas:", ToString(Stats.RoundCount)),
        std::make_pair("Hits:", ToString(Stats.HitCount)),
        std::make_pair("Stands:", ToString(Stats.StandCount)),
        std::make_pair("Doubles:", ToString(Stats.DoubleCount)),
        std::make_pair("Blackjacks:", ToString(Stats.BlackjackCount)),
        std::make_pair("Busts:", ToString(Stats.BustedCount)),
        std::make_pair("Dinheiro gasto:", ToString(Stats.TotalMoneyBetPlayers) + "€"),
        std::make_pair("Dinheiro recebido:", ToString(Stats.TotalMoneyReceivedPlayers) + "€"),
        std::make_pair("Jogador que ganhou mais:", Stats.PlayerWonMoreMoney ? (Stats.PlayerWonMoreMoney->GetName() + " (" + ToString(Stats.PlayerLostMoreMoney->GetBalanceDiff()) + "€)") : "N/A"),
        std::make_pair("Jogador que perdeu mais:", Stats.PlayerLostMoreMoney ? (Stats.PlayerLostMoreMoney->GetName() + " (" + ToString(Stats.PlayerLostMoreMoney->GetBalanceDiff()) + "€)") : "N/A")
    };

    for (int i = 0; i < 13; ++i)
    {
        y += spacing;
        al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 255, 255), 50, y, ALLEGRO_ALIGN_LEFT, column1[i].first);
        al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 255, 255), 300, y, ALLEGRO_ALIGN_LEFT, column1[i].second.c_str());
    }

    // Second column
}
