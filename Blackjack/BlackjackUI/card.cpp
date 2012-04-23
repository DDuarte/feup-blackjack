#include "utilities.h"
#include "card.h"
#include "blackjack.h"

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

    _backColor = 50 + rand() % 25;
    _isMouseHovered = false;
}

void Card::Draw(float dx, float dy, float angle /*= 0.0*/, bool mouseHov /*= false*/) // angle must be in radians
{
    if (_image == NULL)
    {
        printf("Error: Tried to draw a card (rank: %i, suit: %i) at x: %f y: %f with no image specified", _rank, _suit, dx, dy);
        return;
    }

    float sx = _rank * _frameSize.X;
    float yx = _suit * _frameSize.Y;

    //al_set_target_bitmap(al_get_backbuffer(BlackJack::Instance()->GetDisplay())); // why is this needed?
    al_draw_tinted_scaled_rotated_bitmap_region(_image, sx, yx, _frameSize.X, _frameSize.Y,
        al_map_rgb(255, 255, 255), 0.0, 0.0, dx, dy, 1.0 + mouseHov*0.3, 1.0 + mouseHov*0.3, angle, 0);

}

void Card::DrawBack(float dx, float dy, float angle /*= 0.0*/)
{
    if (_backImage == NULL)
    {
        printf("Error: Tried to draw a card (rank: %i, suit: %i) at x: %f y: %f with no image specified", dx, dy);
        return;
    }

    al_set_target_bitmap(al_get_backbuffer(BlackJack::Instance()->GetDisplay())); // why is this needed?
    al_draw_tinted_bitmap(_backImage, al_map_rgb(_backColor, _backColor, _backColor), dx, dy, 0);
    al_draw_bitmap_region(_backImage, 1, 1, _frameSize.X -1, _frameSize.Y - 1, dx + 1, dy + 1, 0);
}

// Should only be called by S_Game::UnloadContents
void Card::DestroyBitmaps()
{
    al_destroy_bitmap(_image);
    al_destroy_bitmap(_backImage);
}
