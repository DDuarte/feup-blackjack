/*!
 * \file text_log.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#ifndef TEXT_LOG_H
#define TEXT_LOG_H

#include <string>
#include <deque>
#include "utilities.h"

const int MAX_TEXT_SCREEN = 4;
const int TEXT_SIZE = 15;
const Vector2D LOG_POSITION = Vector2D(8.0, 509.0);

/*!
 * \class TextLog
 *
 * \brief Defines a "scrolling" log that is displayed on the screen (player and dealer actions)
 *
 */
class TextLog
{
public:
    //! Constructor
    TextLog();

    //! Adds a line to the log
    void AddString(const char* fmt, ...);
    //! Draws the first 4 more recent lines (MAX_TEXT_SCREEN)
    void Draw();

private:
    std::deque<std::string> _texts;

    static std::string Format(const char *fmt, va_list list);

};

#endif // TEXT_LOG_H
