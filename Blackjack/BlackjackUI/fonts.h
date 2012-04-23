#ifndef FONTS_H
#define FONTS_H

#include "utilities.h"

#include <unordered_map>


struct ALLEGRO_FONT;

// Needed fonts are loaded "on demand" however, since we are using a map,
// fonts will only be loaded once and can be used any number of times.
// At this moment only fonts of the type "Champagne & Limousines" are used
class Fonts
{
public:
    static void UnloadFonts();
    static ALLEGRO_FONT* GetFont(uint size);
    
private:
    static std::unordered_map<uint, ALLEGRO_FONT*> _fonts;
};

#endif // FONTS_H
