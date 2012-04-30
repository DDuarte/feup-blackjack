#ifndef RECTBUTTON_H
#define RECTBUTTON_H

#include "allegroObject.h"
#include "utilities.h"
#include "blackjack.h"
#include "delegate.h"

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class RectButton : public AllegroObject
{
public:

    typedef Delegate<bool (RectButton*)> ButtonHandler;

    // Full featured button
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ALLEGRO_COLOR colorMouseHover, ALLEGRO_COLOR textColor, std::string text, uint fontSize, ButtonHandler funcHandler, bool shadowedText);
    
    // Button with mouseHover without text (with or without callback function)
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ALLEGRO_COLOR colorMouseHover, ButtonHandler funcHandler = ButtonHandler());

    // Button without mouseHover color with text (with or without shadow)
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ALLEGRO_COLOR textColor, std::string text, uint fontSize, ButtonHandler funcHandler, bool shadowedText = false);
    
    // Button without mouseHover color without text (with or without callback function)
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ButtonHandler funcHandler = ButtonHandler());

    // Transparent button with text (with or without shadow)
    RectButton(Vector2D position, ALLEGRO_COLOR textColor, std::string text, uint fontSize, ButtonHandler funcHandler, bool shadowedText = false);

    // Transparent button without text (with or without callback function)
    RectButton(Vector2D size, Vector2D position, ButtonHandler funcHandler = ButtonHandler());

    bool Update(ALLEGRO_EVENT* ev);
    void Draw();
    void Draw(bool forcedMouseHovered) { _forcedMouseHovered = forcedMouseHovered; Draw(); }

    std::string GetText() { return _text; }

    bool IsMouseHovered();

private:
    Vector2D _size;
    Vector2D _position;
    std::string _text;

    bool _clicked;
    bool _shadowedText;
    ALLEGRO_COLOR _color;
    ALLEGRO_COLOR _colorMouseHover;
    ALLEGRO_COLOR _textColor;
    
    ButtonHandler _funcHandler;
    //bool (*_func)(RectButton*);
    
    uint _fontSize;

    bool _forcedMouseHovered;
};

#endif // RECTBUTTON_H
