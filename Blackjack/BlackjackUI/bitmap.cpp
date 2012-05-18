/*!
 * \file bitmap.cpp
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#include "bitmap.h"
#include "bitmaps.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

// Default Constructor
Bitmap::Bitmap()
    : _image(-1), _destinationCoordinates(0,0), _sourceCoordinates(0,0), _size(0,0), _centerCoordinates(0,0), _scale(1,1), _tint(al_map_rgb(255,255,255)), _angle(0), _flags(0) { }

// Basic Bitmap
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(0,0), _size((image != -1 ? al_get_bitmap_width(GetImage()) : 0),(image != -1 ? al_get_bitmap_height(GetImage()) : 0)), _centerCoordinates(0,0), _scale(1,1), _tint(al_map_rgb(255,255,255)), _angle(0), _flags(flags) { }

// Tinted Bitmap
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, ALLEGRO_COLOR tint, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(0,0), _size((image != -1 ? al_get_bitmap_width(GetImage()) : 0),(image != -1 ? al_get_bitmap_height(GetImage()) : 0)), _centerCoordinates(0,0), _scale(1,1), _tint(tint), _angle(0), _flags(flags) { }

// Scaled Bitmap
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D scale, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(0,0), _size((image != -1 ? al_get_bitmap_width(GetImage()) : 0),(image != -1 ? al_get_bitmap_height(GetImage()) : 0)), _centerCoordinates(0,0), _scale(scale), _tint(al_map_rgb(255,255,255)), _angle(0), _flags(flags) { }

// Rotated Bitmap
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D centerCoordinates, float angle, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(0,0), _size((image != -1 ? al_get_bitmap_width(GetImage()) : 0),(image != -1 ? al_get_bitmap_height(GetImage()) : 0)), _centerCoordinates(centerCoordinates), _scale(1,1), _tint(al_map_rgb(255,255,255)), _angle(angle), _flags(flags) { }

// Bitmap Region
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(sourceCoordinates), _size(size), _centerCoordinates(0,0), _scale(1,1), _tint(al_map_rgb(255,255,255)), _angle(0), _flags(flags) { }

// Tinted Bitmap Region
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, ALLEGRO_COLOR tint, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(sourceCoordinates), _size(size), _centerCoordinates(0,0), _scale(1,1), _tint(tint), _angle(0), _flags(flags) { }

// Scaled Bitmap Region
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D scale, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(sourceCoordinates), _size(size), _centerCoordinates(0,0), _scale(scale), _tint(al_map_rgb(255,255,255)), _angle(0), _flags(flags) { }

// Rotated Bitmap Region
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, float angle, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(sourceCoordinates), _size(size), _centerCoordinates(centerCoordinates), _scale(1,1), _tint(al_map_rgb(255,255,255)), _angle(angle), _flags(flags) { }

// Tinted Scaled Bitmap
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D scale, ALLEGRO_COLOR tint, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(0,0), _size((image != -1 ? al_get_bitmap_width(GetImage()) : 0),(image != -1 ? al_get_bitmap_height(GetImage()) : 0)), _centerCoordinates(0,0), _scale(scale), _tint(tint), _angle(0), _flags(flags) { }

// Tinted Rotated Bitmap
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D centerCoordinates, ALLEGRO_COLOR tint,  float angle, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(0,0), _size((image != -1 ? al_get_bitmap_width(GetImage()) : 0),(image != -1 ? al_get_bitmap_height(GetImage()) : 0)), _centerCoordinates(centerCoordinates), _scale(1,1), _tint(tint), _angle(angle), _flags(flags) { }

// Scaled Rotated Bitmap
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D centerCoordinates, Vector2D scale, float angle, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(0,0), _size((image != -1 ? al_get_bitmap_width(GetImage()) : 0),(image != -1 ? al_get_bitmap_height(GetImage()) : 0)), _centerCoordinates(centerCoordinates), _scale(scale), _tint(al_map_rgb(255,255,255)), _angle(angle), _flags(flags) { }

// Tinted Scaled Bitmap Region
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, Vector2D scale, ALLEGRO_COLOR tint, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(sourceCoordinates), _size(size), _centerCoordinates(centerCoordinates), _scale(scale), _tint(tint), _angle(0), _flags(flags) { }

// Tinted Rotated Bitmap Region
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, ALLEGRO_COLOR tint,  float angle, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(sourceCoordinates), _size(size), _centerCoordinates(centerCoordinates), _scale(1,1), _tint(tint), _angle(angle), _flags(flags) { }

// Scaled Rotated Bitmap Region
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, Vector2D scale, float angle, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(sourceCoordinates), _size(size), _centerCoordinates(centerCoordinates), _scale(scale), _tint(al_map_rgb(255,255,255)), _angle(angle), _flags(flags) { }

// Tinted Scaled Rotated Bitmap
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D centerCoordinates, Vector2D scale, ALLEGRO_COLOR tint, float angle, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(0,0), _size((image != -1 ? al_get_bitmap_width(GetImage()) : 0),(image != -1 ? al_get_bitmap_height(GetImage()) : 0)), _centerCoordinates(centerCoordinates), _scale(scale), _tint(tint), _angle(angle), _flags(flags) { }

// Tinted Scaled Rotated Bitmap Region
Bitmap::Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, Vector2D scale, ALLEGRO_COLOR tint, float angle, int flags /*= 0*/)
    : _image(image), _destinationCoordinates(destinationCoordinates), _sourceCoordinates(sourceCoordinates), _size(size), _centerCoordinates(centerCoordinates), _scale(scale), _tint(tint), _angle(angle), _flags(flags) { }

void Bitmap::Draw()
{
    if(_image != -1)
        al_draw_tinted_scaled_rotated_bitmap_region(GetImage(), _sourceCoordinates.X, _sourceCoordinates.Y, _size.X, _size.Y, _tint, _centerCoordinates.X, _centerCoordinates.Y, _destinationCoordinates.X, _destinationCoordinates.Y, _scale.X, _scale.Y, _angle, _flags);
}