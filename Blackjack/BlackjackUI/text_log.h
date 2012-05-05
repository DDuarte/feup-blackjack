#ifndef TEXT_LOG_H
#define TEXT_LOG_H

#include <string>
#include <deque>
#include "utilities.h"

const int MAX_TEXT_SCREEN = 4;
const int TEXT_SIZE = 15;
const Vector2D LOG_POSITION = Vector2D(8.0, 509.0);

class TextLog
{
public:
    TextLog();

    void AddString(const char* fmt, ...);
    void Draw();

private:
    std::deque<std::string> _texts;

    static std::string Format(const char *fmt, va_list list);

};

#endif // TEXT_LOG_H
