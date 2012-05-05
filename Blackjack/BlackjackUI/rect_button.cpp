#include "rect_button.h"
#include "utilities.h"
#include "fonts.h"
#include "game_exceptions.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <string>

// Full featured button
RectButton::RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ALLEGRO_COLOR colorMouseHover, ALLEGRO_COLOR textColor, std::string text, uint fontSize, ButtonHandler funcHandler, bool shadowedText)
    : _size(size), _position(position), _color(color), _colorMouseHover(colorMouseHover), _textColor(textColor), _text(text), _fontSize(fontSize), _clicked(false), _funcHandler(funcHandler), _shadowedText(shadowedText), _forcedMouseHovered(false) { }

// Button with mouseHover without text (with or without callback function)
RectButton::RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ALLEGRO_COLOR colorMouseHover, ButtonHandler funcHandler /*= NULL*/ )
    : _size(size), _position(position), _color(color), _colorMouseHover(colorMouseHover), _textColor(ALLEGRO_COLOR()), _text(""), _fontSize(0), _clicked(false), _funcHandler(funcHandler), _shadowedText(false), _forcedMouseHovered(false) { }

// Button without mouseHover color with text (with or without shadow)
RectButton::RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ALLEGRO_COLOR textColor, std::string text, uint fontSize, ButtonHandler funcHandler, bool shadowedText /*= false*/ )
    : _size(size), _position(position), _color(color), _colorMouseHover(ALLEGRO_COLOR()), _textColor(textColor), _text(text), _fontSize(fontSize), _clicked(false), _funcHandler(funcHandler), _shadowedText(shadowedText), _forcedMouseHovered(false) { }

// Button without mouseHover color without text (with or without callback function)
RectButton::RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ButtonHandler funcHandler /*= NULL*/ )
    : _size(size), _position(position), _color(color), _colorMouseHover(ALLEGRO_COLOR()), _textColor(ALLEGRO_COLOR()), _text(""), _fontSize(0), _clicked(false), _funcHandler(funcHandler), _shadowedText(false), _forcedMouseHovered(false) { }

// Transparent button with text (with or without shadow)
RectButton::RectButton(Vector2D position, ALLEGRO_COLOR textColor, std::string text, uint fontSize, ButtonHandler funcHandler, bool shadowedText /*= false*/ )
    : _size(Vector2D(0.0f, 0.0f)), _position(position), _color(ALLEGRO_COLOR()), _colorMouseHover(ALLEGRO_COLOR()), _textColor(textColor), _text(text), _fontSize(fontSize), _clicked(false), _funcHandler(funcHandler), _shadowedText(shadowedText), _forcedMouseHovered(false) { }

// Transparent button without text (with or without callback function)
RectButton::RectButton(Vector2D size, Vector2D position, ButtonHandler funcHandler /*= NULL*/ )
    : _size(size), _position(position), _color(ALLEGRO_COLOR()), _colorMouseHover(ALLEGRO_COLOR()), _textColor(ALLEGRO_COLOR()), _text(""), _fontSize(0), _clicked(false), _funcHandler(funcHandler), _shadowedText(false), _forcedMouseHovered(false) { }

void RectButton::Draw()
{
    uint x = _position.X + _clicked;
    uint y = _position.Y + _clicked;

    if (!_size.X && !_size.Y)
    {
        if (_text.length() != 0)
            _size.X = Fonts::GetFont(_fontSize)->vtable->text_length(Fonts::GetFont(_fontSize), al_ustr_new(_text.c_str()));
        _size.Y = Fonts::GetFont(_fontSize)->height - 10;
    }

    al_draw_filled_rectangle(x, y, x + _size.X, y + _size.Y, (IsMouseHovered() ? _colorMouseHover : _color));

    if (_fontSize && !_text.empty())
    {
        if(_shadowedText)
            al_draw_text(Fonts::GetFont(_fontSize), al_map_rgb(0,0,0), x + 1.0, y + 1.0, 0, _text.c_str());

        ALLEGRO_COLOR selectedTextColor = _textColor;
        if (IsMouseHovered() || _forcedMouseHovered)
            selectedTextColor = al_map_rgb(255, 255, 255);

        al_draw_text(Fonts::GetFont(_fontSize), selectedTextColor, x, y, 0, _text.c_str());
    }
}

bool RectButton::Update(ALLEGRO_EVENT* ev)
{
    if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        if ((ev->mouse.button == 1) && IsMouseHovered())
            _clicked = true;
    if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        if ((ev->mouse.button == 1) && !IsMouseHovered())
            _clicked = false;
        else if ((ev->mouse.button == 1) && _clicked)
        {
            if(!_funcHandler.IsNULL() && IsMouseHovered())
            {
                _clicked = false;
                try
                {
                    return _funcHandler.Invoke(const_cast<RectButton*>(this));
                }
                catch (InvalidDelegateException)
                {   
                    return false;
                }
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
