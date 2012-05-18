/*!
 * \file card.cpp
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#include "utilities.h"
#include "card.h"
#include "blackjack.h"
#include "fonts.h"
#include "localization.h"
#include "bitmaps.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <string>
#include <sstream>

Vector2D Card::_frameSize = CARD_SIZE;

Card::Card(int suit, int rank)
    : _rank(rank), _suit(suit), _score(SCORES[rank])
{

    _backColorRGB = 50 + rand() % 25; // variations of dark grey, "3D" effect

    _bitmap = Bitmap(BITMAP_GAME_CARDS_SPRITE, GetPosition(), Vector2D(_rank * _frameSize.X, _suit * _frameSize.Y), _frameSize);
}

void Card::Draw(float angle /*= 0.0*/, bool mouseHovered /*= false*/, bool drawBack/*=false*/) // angle must be in radians
{
    float sx = _rank * _frameSize.X;
    float sy = _suit * _frameSize.Y;

    if (drawBack)
    {
        static Bitmap backTemp(BITMAP_GAME_CARDS_BACK_SPRITE, Vector2D(GetPosition().X + 1, GetPosition().Y + 1),Vector2D(1,1),Vector2D(_frameSize.X - 1, _frameSize.Y - 1),Vector2D(0,0),Vector2D(1.0 + mouseHovered*0.3, 1.0 + mouseHovered*0.3),al_map_rgb(255,255,255),angle);
        backTemp.Draw();

        backTemp.SetDestinationCoordinates(GetPosition()).SetTint(al_map_rgb(_backColorRGB, _backColorRGB, _backColorRGB)).Draw();

        backTemp.SetDestinationCoordinates(Vector2D(GetPosition().X + 1, GetPosition().Y + 1)).SetTint(al_map_rgb(255,255,255)).Draw();
    }
    else
    {
        if (mouseHovered) // score top left
        {
            _bitmap.SetScale(Vector2D(1.3,1.3)).Draw();
            _bitmap.SetScale(Vector2D(1,1));
            al_draw_filled_rectangle(GetPosition().X + _frameSize.X*1.3 -25, GetPosition().Y + 4, GetPosition().X+_frameSize.X*1.3 - 4, GetPosition().Y + 25, al_map_rgb(255,255,255));
            al_draw_textf(Fonts::GetFont(20), al_map_rgb(0,0,0), GetPosition().X+_frameSize.X*1.3 - 4 , GetPosition().Y, ALLEGRO_ALIGN_RIGHT, "%i", _score);
        }
        else
            _bitmap.Draw();
    }
}

std::string Card::GetName() const
{
    std::stringstream ss("[");
    ss << GetStr((Strings)(_rank + STR_NAMES + 1));
    ss << " - ";
    ss << GetStr((Strings)(_suit + STR_SUITS + 1));

    return ss.str();
}
