#ifndef BITMAP_H
#define BITMAP_H

#include "utilities.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>

class Bitmap
{
public:
    // Default Constructor
    Bitmap();

    // Basic Bitmap
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, int flags = 0);

    // Tinted Bitmap
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, ALLEGRO_COLOR tint, int flags = 0);

    // Scaled Bitmap
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D scale, int flags = 0);

    // Rotated Bitmap
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D centerCoordinates, float angle, int flags = 0);

    // Bitmap Region
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, int flags = 0);

    // Tinted Bitmap Region
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, ALLEGRO_COLOR tint, int flags = 0);

    // Scaled Bitmap Region
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D scale, int flags = 0);

    // Rotated Bitmap Region
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, float angle, int flags = 0);

    // Tinted Scaled Bitmap
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D scale, ALLEGRO_COLOR tint, int flags = 0);

    // Tinted Rotated Bitmap
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D centerCoordinates, ALLEGRO_COLOR tint,  float angle, int flags = 0);

    // Scaled Rotated Bitmap
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D centerCoordinates, Vector2D scale, float angle, int flags = 0);

    // Tinted Scaled Bitmap Region
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, Vector2D scale, ALLEGRO_COLOR tint, int flags = 0);

    // Tinted Rotated Bitmap Region
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, ALLEGRO_COLOR tint,  float angle, int flags = 0);

    // Scaled Rotated Bitmap Region
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, Vector2D scale, float angle, int flags = 0);

    // Tinted Scaled Rotated Bitmap
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D centerCoordinates, Vector2D scale, ALLEGRO_COLOR tint, float angle, int flags = 0);

    // Tinted Scaled Rotated Bitmap Region
    Bitmap(ALLEGRO_BITMAP* image, Vector2D destinationCoordinates, Vector2D sourceCoordinates, Vector2D size, Vector2D centerCoordinates, Vector2D scale, ALLEGRO_COLOR tint, float angle, int flags = 0);

    //~Bitmap();

    ALLEGRO_BITMAP* GetImage() const { return _image; }
    void SetImage(ALLEGRO_BITMAP* val) { _image = val; }

    ALLEGRO_COLOR GetTint() const { return _tint; }
    void SetTint(ALLEGRO_COLOR val) { _tint = val; }

    Vector2D GetSize() const { return _size; }
    void SetSize(Vector2D val) { _size = val; }

    Vector2D GetDestinationCoordinates() const { return _destinationCoordinates; }
    void SetDestinationCoordinates(Vector2D val) { _destinationCoordinates = val; }

    Vector2D GetSourceCoordinates() const { return _sourceCoordinates; }
    void SetSourceCoordinates(Vector2D val) { _sourceCoordinates = val; }

    Vector2D GetCenterCoordinates() const { return _centerCoordinates; }
    void SetCenterCoordinates(Vector2D val) { _centerCoordinates = val; }

    Vector2D GetScale() const { return _scale; }
    void SetScale(Vector2D val) { _scale = val; }

    float GetAngle() const { return _angle; }
    void SetAngle(float val) { _angle = val; }

    int GetFlags() const { return _flags; }
    void SetFlags(int val) { _flags = val; }

    void Draw();
protected:
    ALLEGRO_BITMAP* _image;
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