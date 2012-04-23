#include "fonts.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

ALLEGRO_FONT* Fonts::_font10 = NULL;
ALLEGRO_FONT* Fonts::_font20 = NULL;
ALLEGRO_FONT* Fonts::_font50 = NULL;
ALLEGRO_FONT* Fonts::_font140 = NULL;

void Fonts::LoadFonts()
{
    _font10 = al_load_font("../../Resources/fonts/Champagne & Limousines.ttf", 10, 0);
    _font20 = al_load_font("../../Resources/fonts/Champagne & Limousines.ttf", 20, 0);
    _font50 = al_load_font("../../Resources/fonts/Champagne & Limousines.ttf", 50, 0);
    _font140 = al_load_font("../../Resources/fonts/Champagne & Limousines.ttf", 140, 0);
}

void Fonts::UnloadFonts()
{
    al_destroy_font(_font10);
    al_destroy_font(_font20);
    al_destroy_font(_font50);
    al_destroy_font(_font140);
}
