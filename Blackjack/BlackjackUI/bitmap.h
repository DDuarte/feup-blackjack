#ifndef BITMAP_H
#define BITMAP_H

#include "utilities.h"
#include "bitmaps.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>

class Bitmap
{
public:
    // Default Constructor
    Bitmap();

    // Basic Bitmap
    Bitmap(int image, Vector2D destinationCoordinates = Vector2D(0,0), int flags = 0);

    // Tinted Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, ALLEGRO_COLOR tint, int flags = 0);

    // Scaled Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D scale, int flags = 0);

    // Rotated Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D centerCoordinates, float angle, int flags = 0);

    // Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, int flags = 0);

    // Tinted Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, ALLEGRO_COLOR tint, int flags = 0);

    // Scaled Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D scale, int flags = 0);

    // Rotated Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, float angle, int flags = 0);

    // Tinted Scaled Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D scale, ALLEGRO_COLOR tint, int flags = 0);

    // Tinted Rotated Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D centerCoordinates, ALLEGRO_COLOR tint,  float angle, int flags = 0);

    // Scaled Rotated Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D centerCoordinates, Vector2D scale, float angle, int flags = 0);

    // Tinted Scaled Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, Vector2D scale, ALLEGRO_COLOR tint, int flags = 0);

    // Tinted Rotated Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, ALLEGRO_COLOR tint,  float angle, int flags = 0);

    // Scaled Rotated Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, Vector2D scale, float angle, int flags = 0);

    // Tinted Scaled Rotated Bitmap
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D centerCoordinates, Vector2D scale, ALLEGRO_COLOR tint, float angle, int flags = 0);

    // Tinted Scaled Rotated Bitmap Region
    Bitmap(int image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, Vector2D scale, ALLEGRO_COLOR tint, float angle, int flags = 0);

    //~Bitmap();

    ALLEGRO_BITMAP* GetImage() const { return Bitmaps::GetBitmap(_image); }
    //void SetImage(int val) { _image = val; }

    ALLEGRO_COLOR GetTint() const { return _tint; }
    Bitmap& SetTint(ALLEGRO_COLOR val) { _tint = val; return *this; }

    Vector2D GetSize() const { return _size; }
    Bitmap& SetSize(Vector2D val) { _size = val; return *this; }

    Vector2D GetDestinationCoordinates() const { return _destinationCoordinates; }
    Bitmap& SetDestinationCoordinates(Vector2D val) { _destinationCoordinates = val; return *this; }

    Vector2D GetSourceCoordinates() const { return _sourceCoordinates; }
    Bitmap& SetSourceCoordinates(Vector2D val) { _sourceCoordinates = val; return *this; }

    Vector2D GetCenterCoordinates() const { return _centerCoordinates; }
    Bitmap& SetCenterCoordinates(Vector2D val) { _centerCoordinates = val; return *this;}

    Vector2D GetScale() const { return _scale; }
    Bitmap& SetScale(Vector2D val) { _scale = val;  return *this;}

    float GetAngle() const { return _angle; }
    Bitmap& SetAngle(float val) { _angle = val; return *this;}

    int GetFlags() const { return _flags; }
    Bitmap& SetFlags(int val) { _flags = val; return *this; }

    void Draw();

protected:
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
