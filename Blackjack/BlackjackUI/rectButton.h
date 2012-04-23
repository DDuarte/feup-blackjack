#ifndef RECTBUTTON_H
#define RECTBUTTON_H

#include "allegroObject.h"
#include "utilities.h"
#include "blackjack.h"

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class RectButton : public AllegroObject
{
public:
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ALLEGRO_COLOR colorMouseHover, ALLEGRO_COLOR textColor, std::string text, uint fontSize, bool func(RectButton*) = NULL);
    void Draw();
    bool Update(ALLEGRO_EVENT* ev);

private:
    Vector2D _size;
    Vector2D _position;
    std::string _text;

    bool _clicked;

    ALLEGRO_COLOR _color;
    ALLEGRO_COLOR _colorMouseHover;
    ALLEGRO_COLOR _textColor;

    bool (*_func)(RectButton*);

    uint _fontSize;

    bool IsMouseHover() { return ((BlackJack::GetMousePosition().X <= _position.X + _size.X) && (BlackJack::GetMousePosition().X >= _position.X) &&(BlackJack::GetMousePosition().Y <= _position.Y + _size.Y) && (BlackJack::GetMousePosition().Y >=  _position.Y)); }
};

#endif // RECTBUTTON_H