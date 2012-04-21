#include "utilities.h"
#include "card.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <string>
#include <sstream>

Card::Card(int suit, int rank, uint score, ALLEGRO_BITMAP* image)
    : _rank(rank), _suit(suit), _score(score), _image(image), _frameSize(CARD_SIZE) { }

void Card::Draw(ALLEGRO_DISPLAY* display, float dx, float dy)
{
    float sx = _rank * _frameSize.X;
    float yx = _suit * _frameSize.Y;

    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap_region(_image, sx, yx, _frameSize.X, _frameSize.Y, dx, dy, 0); 
}
