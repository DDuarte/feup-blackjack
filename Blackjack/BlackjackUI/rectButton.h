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
    // Full featured button
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR* color, ALLEGRO_COLOR* colorMouseHover, ALLEGRO_COLOR* textColor, std::string text, uint fontSize, bool func(RectButton*), bool shadowedText);
    
    // Button with mouseHover without text (with or without callback function)
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR* color, ALLEGRO_COLOR* colorMouseHover, bool func(RectButton*) = NULL);

    // Button without mouseHover color with text (with or without shadow)
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR* color, ALLEGRO_COLOR* textColor, std::string text, uint fontSize, bool func(RectButton*), bool shadowedText = false);
    
    // Button without mouseHover color without text (with or without callback function)
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR* color, bool func(RectButton*) = NULL);

    // Transparent button with text (with or without shadow)
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR* textColor, std::string text, uint fontSize, bool func(RectButton*), bool shadowedText = false);

    // Transparent button without text (with or without callback function)
    RectButton(Vector2D size, Vector2D position, bool func(RectButton*) = NULL);

    void Draw();
    bool Update(ALLEGRO_EVENT* ev);

private:
    Vector2D _size;
    Vector2D _position;
    std::string _text;

    bool _clicked;
    bool _shadowedText;
    ALLEGRO_COLOR* _color;
    ALLEGRO_COLOR* _colorMouseHover;
    ALLEGRO_COLOR* _textColor;

    bool (*_func)(RectButton*);

    uint _fontSize;

    bool IsMouseHovered();
};

#endif // RECTBUTTON_H