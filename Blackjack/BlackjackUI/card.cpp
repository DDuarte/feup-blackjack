#include "utilities.h"
#include "card.h"
#include "blackjack.h"
#include "fonts.h"
#include "localization.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <string>
#include <sstream>

ALLEGRO_BITMAP* Card::_image = NULL;
ALLEGRO_BITMAP* Card::_backImage = NULL;
Vector2D Card::_frameSize = CARD_SIZE;

Card::Card(int suit, int rank)
    : _rank(rank), _suit(suit), _score(SCORES[rank])
{
    if (_image == NULL)
        _image = al_load_bitmap("../../Resources/Sprites/card_sprites.png");
    if (_backImage == NULL)
        _backImage = al_load_bitmap("../../Resources/cards/b1fv.png");

    _backColorRGB = 50 + rand() % 25; // variations of dark grey, "3D" effect

    _BMP = Bitmap(_image, GetPosition(), Vector2D(_rank * _frameSize.X, _suit * _frameSize.Y), _frameSize);
}

void Card::Draw(float angle /*= 0.0*/, bool mouseHovered /*= false*/, bool drawBack/*=false*/) // angle must be in radians
{
    if (_backImage == NULL && drawBack)
    {
        printf("Error: Tried to draw a back card at x: %f y: %f with no image specified", GetPosition().X, GetPosition().Y);
        return;
    }

    if (_image == NULL && !drawBack)
    {
        printf("Error: Tried to draw a card (rank: %i, suit: %i) at x: %f y: %f with no image specified", _rank, _suit, GetPosition().X, GetPosition().Y);
        return;
    }

    float sx = _rank * _frameSize.X;
    float sy = _suit * _frameSize.Y;

    if (drawBack)
    {
        Bitmap backTemp(_backImage, Vector2D(GetPosition().X + 1, GetPosition().Y + 1),Vector2D(1,1),Vector2D(_frameSize.X - 1, _frameSize.Y - 1),Vector2D(0,0),Vector2D(1.0 + mouseHovered*0.3, 1.0 + mouseHovered*0.3),al_map_rgb(255,255,255),angle);
        backTemp.Draw();

        backTemp.SetDestinationCoordinates(GetPosition());
        backTemp.SetTint(al_map_rgb(_backColorRGB, _backColorRGB, _backColorRGB));
        backTemp.Draw();

        backTemp.SetDestinationCoordinates(Vector2D(GetPosition().X + 1, GetPosition().Y + 1));
        backTemp.SetTint(al_map_rgb(255,255,255));
        backTemp.Draw();
    }
    else
    {
        if (mouseHovered) // score top left
        {
            _BMP.SetScale(Vector2D(1.3,1.3));
            _BMP.Draw();
            _BMP.SetScale(Vector2D(1,1));
            al_draw_filled_rectangle(GetPosition().X + _frameSize.X*1.3 -25, GetPosition().Y + 4, GetPosition().X+_frameSize.X*1.3 - 4, GetPosition().Y + 25, al_map_rgb(255,255,255));
            al_draw_textf(Fonts::GetFont(20), al_map_rgb(0,0,0), GetPosition().X+_frameSize.X*1.3 - 4 , GetPosition().Y, ALLEGRO_ALIGN_RIGHT, "%i", _score);
        }
        else
            _BMP.Draw();
    }
}

// Should only be called by S_Game::UnloadContents
void Card::DestroyBitmaps()
{
    al_destroy_bitmap(_image);
    al_destroy_bitmap(_backImage);
}

std::string Card::GetName() const
{
    std::stringstream ss("[");
    ss << GetStr((Strings)(_rank + STR_NAMES + 1));
    ss << " - ";
    ss << GetStr((Strings)(_suit + STR_SUITS + 1));

    return ss.str();
}
