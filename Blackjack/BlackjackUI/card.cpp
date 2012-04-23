#include "utilities.h"
#include "card.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <string>
#include <sstream>

ALLEGRO_BITMAP* Card::_image = NULL;
ALLEGRO_BITMAP* Card::_backImage = NULL;
Vector2D Card::_frameSize = CARD_SIZE;

Card::Card(int suit, int rank, uint score)
    : _rank(rank), _suit(suit), _score(score)
{
    if (_image == NULL)
        _image = al_load_bitmap("../../Resources/Sprites/card_sprites.png");
    if (_backImage == NULL)
        _backImage = al_load_bitmap("../../Resources/cards/b1fv.png");
}

void Card::Draw(ALLEGRO_DISPLAY* display, float dx, float dy, float angle /*= 0.0*/) // angle must be in radians
{
    if (_image == NULL)
    {
        printf("Error: Tried to draw a card (rank: %i, suit: %i) at x: %f y: %f with no image specified", _rank, _suit, dx, dy);
        return;
    }

    float sx = _rank * _frameSize.X;
    float yx = _suit * _frameSize.Y;

    al_set_target_bitmap(al_get_backbuffer(display)); // why is this needed?
    al_draw_tinted_scaled_rotated_bitmap_region(_image, sx, yx, _frameSize.X, _frameSize.Y,
        al_map_rgb(255, 255, 255), 0.0, 0.0, dx, dy, 1.0, 1.0, angle, 0);
}

void Card::DrawBack(ALLEGRO_DISPLAY* display, float dx, float dy, float angle /*= 0.0*/)
{
    if (_backImage == NULL)
    {
        printf("Error: Tried to draw a card (rank: %i, suit: %i) at x: %f y: %f with no image specified", dx, dy);
        return;
    }

    al_set_target_bitmap(al_get_backbuffer(display)); // why is this needed?
    al_draw_bitmap(_backImage, dx, dy, 0);
}

// Should only be called by S_Game::UnloadContents
void Card::DestroyBitmaps()
{
    al_destroy_bitmap(_image);
    al_destroy_bitmap(_backImage);
}
