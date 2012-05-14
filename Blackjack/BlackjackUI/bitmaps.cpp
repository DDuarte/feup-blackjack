#include "bitmaps.h"
#include "utilities.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <map>
#include <string>

std::map<std::string, ALLEGRO_BITMAP*> Bitmaps::_bitmaps = std::map<std::string, ALLEGRO_BITMAP*>();

void Bitmaps::UnloadBitmaps()
{
    for (std::map<std::string, ALLEGRO_BITMAP*>::iterator bmp = _bitmaps.begin(); bmp != _bitmaps.end(); ++bmp)
        al_destroy_bitmap(bmp->second);
}

ALLEGRO_BITMAP* Bitmaps::GetBitmap(int bitmaps_path_number)
{
    if (_bitmaps.find(bitmaps_path[bitmaps_path_number]) == _bitmaps.end())
        _bitmaps[bitmaps_path[bitmaps_path_number]] = al_load_bitmap(bitmaps_path[bitmaps_path_number].c_str());

    return _bitmaps[bitmaps_path[bitmaps_path_number]];
}
