#include "rectButton.h"
#include "utilities.h"
#include "fonts.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <string>

// Full featured button
RectButton::RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR* color, ALLEGRO_COLOR* colorMouseHover, ALLEGRO_COLOR* textColor, std::string text, uint fontSize, bool func(RectButton*), bool shadowedText)
    : _size(size), _position(position), _color(color), _colorMouseHover(colorMouseHover), _textColor(textColor), _text(text), _fontSize(fontSize), _clicked(false), _func(func), _shadowedText(shadowedText) { }

// Button with mouseHover without text (with or without callback function)
RectButton::RectButton( Vector2D size, Vector2D position, ALLEGRO_COLOR* color, ALLEGRO_COLOR* colorMouseHover, bool func(RectButton*) /*= NULL*/ )
    : _size(size), _position(position), _color(color), _colorMouseHover(colorMouseHover), _textColor(NULL), _text(""), _fontSize(0), _clicked(false), _func(func), _shadowedText(false) { }

// Button without mouseHover color with text (with or without shadow)
RectButton::RectButton( Vector2D size, Vector2D position, ALLEGRO_COLOR* color, ALLEGRO_COLOR* textColor, std::string text, uint fontSize, bool func(RectButton*), bool shadowedText /*= false*/ )
    : _size(size), _position(position), _color(color), _colorMouseHover(NULL), _textColor(textColor), _text(text), _fontSize(fontSize), _clicked(false), _func(func), _shadowedText(shadowedText) { }

// Button without mouseHover color without text (with or without callback function)
RectButton::RectButton( Vector2D size, Vector2D position, ALLEGRO_COLOR* color, bool func(RectButton*) /*= NULL*/ )
    : _size(size), _position(position), _color(color), _colorMouseHover(NULL), _textColor(NULL), _text(""), _fontSize(0), _clicked(false), _func(func), _shadowedText(false) { }

// Transparent button with text (with or without shadow)
RectButton::RectButton( Vector2D size, Vector2D position, ALLEGRO_COLOR* textColor, std::string text, uint fontSize, bool func(RectButton*), bool shadowedText /*= false*/ )
    : _size(size), _position(position), _color(NULL), _colorMouseHover(NULL), _textColor(textColor), _text(text), _fontSize(fontSize), _clicked(false), _func(func), _shadowedText(shadowedText) { }

// Transparent button without text (with or without callback function)
RectButton::RectButton( Vector2D size, Vector2D position, bool func(RectButton*) /*= NULL*/ )
    : _size(size), _position(position), _color(NULL), _colorMouseHover(NULL), _textColor(NULL), _text(""), _fontSize(0), _clicked(false), _func(func), _shadowedText(false) { }

void RectButton::Draw()
{
    uint x = _position.X + _clicked;
    uint y = _position.Y + _clicked;
    if ((IsMouseHovered() ? _colorMouseHover : _color) != NULL)
        al_draw_filled_rectangle(x, y, x + _size.X,y + _size.Y, (IsMouseHovered() ? *_colorMouseHover : *_color));

    if (_fontSize && !_text.empty() && _textColor)
    {
        if(_shadowedText)
            al_draw_text(Fonts::GetFont(_fontSize), al_map_rgb(0,0,0), x + _size.X / 2 + 1, y + _size.Y / 2 - Fonts::GetFont(_fontSize)->height / 2 + 1,ALLEGRO_ALIGN_CENTRE, _text.c_str());

        al_draw_text(Fonts::GetFont(_fontSize), *_textColor, x + _size.X / 2.0, y + _size.Y / 2.0 - Fonts::GetFont(_fontSize)->height / 2.0, ALLEGRO_ALIGN_CENTRE, _text.c_str());
    }
}

bool RectButton::Update(ALLEGRO_EVENT* ev)
{
    if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        if ((ev->mouse.button == 1) && IsMouseHovered())
            _clicked = true;

    if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if ((ev->mouse.button == 1) && _clicked)
        {
            _clicked = false;
            if(_func != NULL && IsMouseHovered())
                (*_func)(this);
        }
    }

    return true;
}

bool RectButton::IsMouseHovered()
{
    return (
        (BlackJack::GetMousePosition().X <= _position.X + _size.X) &&
        (BlackJack::GetMousePosition().Y <= _position.Y + _size.Y) &&
        (BlackJack::GetMousePosition().X >= _position.X) &&
        (BlackJack::GetMousePosition().Y >=  _position.Y));
}
