#include "rectButton.h"
#include "utilities.h"
#include "fonts.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <string>

RectButton::RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ALLEGRO_COLOR colorMouseHover, ALLEGRO_COLOR textColor, std::string text, uint fontSize, bool func(RectButton*))
{
    _size = size;
    _position = position;
    _color = color;
    _colorMouseHover = colorMouseHover;
    _textColor = textColor;
    _text = text;
    _fontSize = fontSize;
    _clicked = false;
    _func = func;
}

void RectButton::Draw()
{
    uint x = _position.X + _clicked;
    uint y = _position.Y + _clicked;
    al_draw_filled_rectangle(x, y, x + _size.X,y + _size.Y, (IsMouseHover() ? _colorMouseHover : _color));

    al_draw_textf(Fonts::GetFont(_fontSize), _textColor, x + _size.X / 2, y + _size.Y / 2 - Fonts::GetFont(_fontSize)->height / 2,ALLEGRO_ALIGN_CENTRE, "%s", _text.c_str());
}

bool RectButton::Update( ALLEGRO_EVENT* ev )
{

    if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        if ((ev->mouse.button == 1) && IsMouseHover())
            _clicked = true;
    if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        if ((ev->mouse.button == 1) && _clicked)
        {
            _clicked = false;
            if(_func != NULL)
                (*_func)(this);
        }


    return true;
}







