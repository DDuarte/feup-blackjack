#include "fonts.h"
#include "utilities.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <unordered_map>

std::unordered_map<uint, ALLEGRO_FONT*> Fonts::_fonts = std::unordered_map<uint, ALLEGRO_FONT*>();

void Fonts::UnloadFonts()
{
    for (std::unordered_map<uint, ALLEGRO_FONT*>::iterator font = _fonts.begin(); font != _fonts.end(); ++font)
        al_destroy_font(font->second);

    _fonts.clear();
}

ALLEGRO_FONT* Fonts::GetFont(uint size)
{
    if (_fonts.find(size) == _fonts.end())
        _fonts[size] = al_load_font("../../Resources/fonts/Champagne & Limousines.ttf", size, 0);

    return _fonts[size];
}
