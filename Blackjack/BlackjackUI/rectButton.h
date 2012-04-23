#ifndef RECTBUTTON_H
#define RECTBUTTON_H

#include "allegroObject.h"
#include "utilities.h"

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class RectButton : public AllegroObject
{
public:
    void Initialize() { }
    void LoadContents() { }
    void Draw() { }
    void Update() { }
    void UnloadContents() { }
private:
    Vector2D _size;
    Vector2D _position;
    std::string _text;

    ALLEGRO_COLOR* _color;
    ALLEGRO_COLOR* _textColor;
};

#endif // RECTBUTTON_H