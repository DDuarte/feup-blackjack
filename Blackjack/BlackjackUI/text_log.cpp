#include "text_log.h"
#include "utilities.h"
#include "fonts.h"

#include <deque>
#include <string>
#include <cstdarg>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

TextLog::TextLog()
{
    _texts = std::deque<std::string>();
}

void TextLog::AddString(const char* fmt, ...)
{
    va_list marker = NULL; 
    va_start(marker, fmt);

    _texts.push_front(Format(fmt, marker));

    va_end(marker);
}

void TextLog::Draw()
{
    for (uint i = 0; i < min(_texts.size(), MAX_TEXT_SCREEN); ++i)
    {
        float posX = LOG_POSITION.X;
        float posY = LOG_POSITION.Y + i * (TEXT_SIZE + 5);

        // this will do a fade out effect for "older" entries
        // last action will be displayed brighter
        int color = 255 - (i * 10);

        al_draw_text(Fonts::GetFont(TEXT_SIZE), al_map_rgb(color, color, color), posX, posY, ALLEGRO_ALIGN_LEFT, _texts.at(i).c_str());

        // Remove texts that are no longer shown
        if (_texts.size() > MAX_TEXT_SCREEN)
            _texts.pop_back();
    }
}

std::string TextLog::Format(const char *fmt, va_list list) // By Nitron, modified
{
    std::string result;

    // Get formatted string length adding one for NULL
    size_t len = _vscprintf(fmt, list) + 1;

    // Create a char vector to hold the formatted string.
    std::vector<char> buffer(len, '\0');
    if (_vsnprintf_s(&buffer[0], buffer.size(), len, fmt, list))
        result = &buffer[0];

    return result; 
}
