/*!
 * \file bitmap.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 *
 */

#ifndef BITMAP_H
#define BITMAP_H

#include "utilities.h"
#include "bitmaps.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>

/*!
 * \class Bitmap
 *
 * \brief  Defines an image that can be draw in the screen
 *
 */
class Bitmap
{
public:
    //! Default Constructor
    Bitmap();

    //! Basic Bitmap
    Bitmap(int image, Vector2D destinationCoordinates = Vector2D(0,0), int flags = 0);

    //! Tinted Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, ALLEGRO_COLOR tint, int flags = 0);

    //! Scaled Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D scale, int flags = 0);

    //! Rotated Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D centerCoordinates, float angle, int flags = 0);

    //! Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, int flags = 0);

    //! Tinted Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, ALLEGRO_COLOR tint, int flags = 0);

    //! Scaled Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D scale, int flags = 0);

    //! Rotated Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, float angle, int flags = 0);

    //! Tinted Scaled Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D scale, ALLEGRO_COLOR tint, int flags = 0);

    //! Tinted Rotated Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D centerCoordinates, ALLEGRO_COLOR tint,  float angle, int flags = 0);

    //! Scaled Rotated Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D centerCoordinates, Vector2D scale, float angle, int flags = 0);

    //! Tinted Scaled Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, Vector2D scale, ALLEGRO_COLOR tint, int flags = 0);

    //! Tinted Rotated Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, ALLEGRO_COLOR tint,  float angle, int flags = 0);

    //! Scaled Rotated Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, Vector2D scale, float angle, int flags = 0);

    //! Tinted Scaled Rotated Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D centerCoordinates, Vector2D scale, ALLEGRO_COLOR tint, float angle, int flags = 0);

    //! Tinted Scaled Rotated Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, Vector2D scale, ALLEGRO_COLOR tint, float angle, int flags = 0);

    //! Retrieves the underlying ALLEGRO_BITMAP used
    ALLEGRO_BITMAP* GetImage() const { return Bitmaps::GetBitmap(_image); }

    //! Returns then ALLEGRO_COLOR used for tint
    ALLEGRO_COLOR GetTint() const { return _tint; }
    //! Changes the thing used
    Bitmap& SetTint(ALLEGRO_COLOR val) { _tint = val; return *this; }

    //! Returns the size of the image
    Vector2D GetSize() const { return _size; }
    //! Changes the size of the image
    Bitmap& SetSize(Vector2D val) { _size = val; return *this; }

    //! Returns the destination coordinates
    Vector2D GetDestinationCoordinates() const { return _destinationCoordinates; }
    //! Changes the destination coordinates
    Bitmap& SetDestinationCoordinates(Vector2D val) { _destinationCoordinates = val; return *this; }

    //! Returns the source coordinates
    Vector2D GetSourceCoordinates() const { return _sourceCoordinates; }
    //! Changes the source coordinates
    Bitmap& SetSourceCoordinates(Vector2D val) { _sourceCoordinates = val; return *this; }

    //! Returns the center coordinates
    Vector2D GetCenterCoordinates() const { return _centerCoordinates; }
    //! Changes the center coordinates
    Bitmap& SetCenterCoordinates(Vector2D val) { _centerCoordinates = val; return *this;}

    //! Returns the scale of the image
    Vector2D GetScale() const { return _scale; }
    //! Changes the scale of the image
    Bitmap& SetScale(Vector2D val) { _scale = val;  return *this;}

    //! Returns the draw angle
    float GetAngle() const { return _angle; }
    //! Changes the draw angle
    Bitmap& SetAngle(float val) { _angle = val; return *this;}

    //! Returns ALLEGRO_BITMAP flags
    int GetFlags() const { return _flags; }
    //! Changes ALLEGRO_BITMAP flags
    Bitmap& SetFlags(int val) { _flags = val; return *this; }

    //! Draws the image to the display
    void Draw();

private:
    int _image;
    ALLEGRO_COLOR _tint;
    Vector2D _size;
    Vector2D _destinationCoordinates;
    Vector2D _sourceCoordinates;
    Vector2D _centerCoordinates;
    Vector2D _scale;
    float _angle;
    int _flags;
};

#endif // BITMAP_H
