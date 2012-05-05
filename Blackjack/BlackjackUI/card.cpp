#include "utilities.h"
#include "card.h"
#include "blackjack.h"
#include "fonts.h"

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
}

void Card::Draw(float dx, float dy, float angle /*= 0.0*/, bool mouseHovered /*= false*/, bool drawBack/*=false*/) // angle must be in radians
{
    if (_backImage == NULL && drawBack)
    {
        printf("Error: Tried to draw a back card at x: %f y: %f with no image specified", dx, dy);
        return;
    }

    if (_image == NULL && !drawBack)
    {
        printf("Error: Tried to draw a card (rank: %i, suit: %i) at x: %f y: %f with no image specified", _rank, _suit, dx, dy);
        return;
    }

    float sx = _rank * _frameSize.X;
    float yx = _suit * _frameSize.Y;

    if (drawBack)
    {
        al_draw_tinted_scaled_rotated_bitmap_region(_backImage, 1, 1, _frameSize.X - 1, _frameSize.Y - 1,
            al_map_rgb(255, 255, 255), 0.0, 0.0, dx + 1, dy + 1, 1.0 + mouseHovered*0.3, 1.0 + mouseHovered*0.3, angle, 0);
        al_draw_tinted_bitmap(_backImage, al_map_rgb(_backColorRGB, _backColorRGB, _backColorRGB), dx, dy, 0);
        al_draw_bitmap_region(_backImage, 1, 1, _frameSize.X -1, _frameSize.Y - 1, dx + 1, dy + 1, 0);
    }
    else
    {
        al_draw_tinted_scaled_rotated_bitmap_region(_image, sx, yx, _frameSize.X, _frameSize.Y,
            al_map_rgb(255, 255, 255), 0.0, 0.0, dx, dy, 1.0 + mouseHovered*0.3, 1.0 + mouseHovered*0.3, angle, 0);

        if (mouseHovered) // score top left
        {
            al_draw_filled_rectangle(dx + _frameSize.X*1.3 -25, dy + 4, dx+_frameSize.X*1.3 - 4, dy + 25, al_map_rgb(255,255,255));
            al_draw_textf(Fonts::GetFont(20), al_map_rgb(0,0,0), dx+_frameSize.X*1.3 - 4 , dy, ALLEGRO_ALIGN_RIGHT, "%i", _score);
        }
    }
}

// Should only be called by S_Game::UnloadContents
void Card::DestroyBitmaps()
{
    al_destroy_bitmap(_image);
    al_destroy_bitmap(_backImage);
}
