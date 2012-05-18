/*!
 * \file rect_button.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#ifndef RECTBUTTON_H
#define RECTBUTTON_H

#include "utilities.h"
#include "delegate.h"

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

/*!
 * \class RectButton
 *
 * \brief Defines a clickable button with multiple style options. When clicked, it can call a function (callback)
 *
 */
class RectButton
{
public:

    typedef Delegate<bool (RectButton*)> ButtonHandler;

    //! Full featured button
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ALLEGRO_COLOR colorMouseHover, ALLEGRO_COLOR textColor, std::string text, uint fontSize, ButtonHandler funcHandler, bool shadowedText);
    
    //! Button with mouseHover without text (with or without callback function)
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ALLEGRO_COLOR colorMouseHover, ButtonHandler funcHandler = ButtonHandler());

    //! Button without mouseHover color with text (with or without shadow)
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ALLEGRO_COLOR textColor, std::string text, uint fontSize, ButtonHandler funcHandler, bool shadowedText = false);
    
    //! Button without mouseHover color without text (with or without callback function)
    RectButton(Vector2D size, Vector2D position, ALLEGRO_COLOR color, ButtonHandler funcHandler = ButtonHandler());

    //! Transparent button with text (with or without shadow)
    RectButton(Vector2D position, ALLEGRO_COLOR textColor, std::string text, uint fontSize, ButtonHandler funcHandler, bool shadowedText = false);

    //! Transparent button without text (with or without callback function)
    RectButton(Vector2D size, Vector2D position, ButtonHandler funcHandler = ButtonHandler());

    //! State actualization
    bool Update(ALLEGRO_EVENT* ev);
    //! Draw to screen
    void Draw();
    //! Draw to screen with forced mouse hovered (special effect)
    void Draw(bool forcedMouseHovered) { _forcedMouseHovered = forcedMouseHovered; Draw(); }

    //! True if button is being hovered by mouse
    bool IsMouseHovered();

    //! Returns the function handler (if set)
    ButtonHandler* Handler() { return &_funcHandler; }

    //! Returns central text
    std::string GetText() const { return _text; }
    //! Changes text button
    void SetText(std::string val) { _text = val; }

    //! Gets or sets button visibility
    bool Visible;

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
    
    uint _fontSize;

    bool _forcedMouseHovered;
};

#endif // RECTBUTTON_H
