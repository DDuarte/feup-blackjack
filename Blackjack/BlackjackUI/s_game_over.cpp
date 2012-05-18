/*!
 * \file s_game_over.cpp
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#include "s_game_over.h"
#include "bitmap.h"
#include "blackjack.h"
#include "s_game.h"
#include "utilities.h"
#include "rect_button.h"
#include "localization.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define Stats S_Game::Statistics

bool ChangeToMenuStateFromGameOver(RectButton* btn);

void S_GameOver::Initialize()
{
    _menuButton = new RectButton(Vector2D(350, 530), al_map_rgb(255, 255, 255), std::string("Menu"), 50, RectButton::ButtonHandler().Bind<&ChangeToMenuStateFromGameOver>(), true);
}

bool S_GameOver::Update(ALLEGRO_EVENT* ev)
{
    if (ev->type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return !BlackJack::Instance()->Quit(true);
    else if (ev->type == ALLEGRO_EVENT_KEY_UP && ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        return !BlackJack::Instance()->Quit(true);
    
    _menuButton->Update(ev);

    return true;
}

void S_GameOver::Draw()
{
    static Bitmap bg(BITMAP_MENU_GAME_OVER);
    bg.Draw();

    // Outer transparent rectangle
    al_draw_filled_rounded_rectangle(40, 119, 760, 495, 10, 10, al_map_rgba(0, 0, 0, 175));
    
    // Draw button
    _menuButton->Draw();

    // First column
    std::pair<std::string, std::string> column1[] =
    {
        std::make_pair(GetStr(STR_STAT_WINNER_IS), Stats.Winner ? Stats.Winner->GetName() : "N/A"),
        std::make_pair(GetStr(STR_STAT_BETS), ToString(Stats.BetCount)),
        std::make_pair(GetStr(STR_STAT_ROUNDS), ToString(Stats.RoundCount)),
        std::make_pair(GetStr(STR_STAT_HITS), ToString(Stats.HitCount)),
        std::make_pair(GetStr(STR_STAT_STANDS), ToString(Stats.StandCount)),
        std::make_pair(GetStr(STR_STAT_DOUBLES), ToString(Stats.DoubleCount)),
        std::make_pair(GetStr(STR_STAT_BJS), ToString(Stats.BlackjackCount)),
        std::make_pair(GetStr(STR_STAT_BUSTS), ToString(Stats.BustedCount)),
        std::make_pair(GetStr(STR_STAT_SPENT_MONEY), ToString(Stats.TotalMoneyBetPlayers) + "€"),
        std::make_pair(GetStr(STR_STAT_RECEIVED_MONEY), ToString(Stats.TotalMoneyReceivedPlayers) + "€"),
        std::make_pair(GetStr(STR_STAT_PLR_WON_MORE), Stats.PlayerWonMoreMoney ? (Stats.PlayerWonMoreMoney->GetName() + " (" + ToString(Stats.PlayerWonMoreMoney->GetBalanceDiff()) + "€)") : "N/A"),
        std::make_pair(GetStr(STR_STAT_PLR_LOST_MORE), Stats.PlayerLostMoreMoney ? (Stats.PlayerLostMoreMoney->GetName() + " (" + ToString(Stats.PlayerLostMoreMoney->GetBalanceDiff()) + "€)") : "N/A")
    };

    int y1 = 119;
    for (int i = 0; i < 12; ++i)
    {
        y1 += 25;
        al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 255, 255), 50, y1, ALLEGRO_ALIGN_LEFT, column1[i].first.c_str());
        al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 255, 255), 300, y1, ALLEGRO_ALIGN_LEFT, column1[i].second.c_str());
    }

    // Second column
    if (!Stats.Players.empty())
    {
        al_draw_line(390, 140, 390, 380, al_map_rgb(255, 255, 255), 1);

        int y2 = 144;
        al_draw_text(Fonts::GetFont(25), al_map_rgb(255, 255, 255), 405, y2, ALLEGRO_ALIGN_LEFT, GetStr(STR_STAT_PLR_HEADER).c_str());

        y2 += 10;

        for (std::vector<Player>::const_iterator itr = Stats.Players.begin(); itr != Stats.Players.end(); ++itr)
        {
            y2 += 25;
            al_draw_text(Fonts::GetFont(20), al_map_rgb(255, 255, 255), 405, y2, ALLEGRO_ALIGN_LEFT, (*itr).GetName().c_str());
            al_draw_textf(Fonts::GetFont(20), al_map_rgb(255, 255, 255), 514, y2, ALLEGRO_ALIGN_LEFT, "%s €", ToString((*itr).GetInitialBalance()).c_str());
            al_draw_textf(Fonts::GetFont(20), al_map_rgb(255, 255, 255), 650, y2, ALLEGRO_ALIGN_LEFT, "%s €", ToString((*itr).GetBalance()).c_str());
        }
    }
}

void S_GameOver::UnloadContents()
{
    delete _menuButton;
}

bool ChangeToMenuStateFromGameOver(RectButton* btn)
{
    BlackJack::Instance()->ChangeState(STATE_MAIN_MENU);
    return false;
}
