#ifndef FONTS_H
#define FONTS_H

#include <map>
#include "utilities.h"

struct ALLEGRO_FONT;

class Fonts
{
public:
    static void UnloadFonts();
    static ALLEGRO_FONT* GetFont(uint size);
    
private:
    static std::map<uint, ALLEGRO_FONT*> _fonts;
};

#endif // FONTS_H
