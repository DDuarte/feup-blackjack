/*!
 * \file bitmaps.cpp
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#include "bitmaps.h"
#include "utilities.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <map>
#include <string>

std::map<std::string, ALLEGRO_BITMAP*> Bitmaps::_bitmaps = std::map<std::string, ALLEGRO_BITMAP*>();

void Bitmaps::UnloadBitmaps()
{
    for (std::map<std::string, ALLEGRO_BITMAP*>::const_iterator bmp = _bitmaps.begin(); bmp != _bitmaps.end(); ++bmp)
        al_destroy_bitmap(bmp->second);

    _bitmaps.clear();
}

ALLEGRO_BITMAP* Bitmaps::GetBitmap(int bitmapsPathNumber)
{
    if (_bitmaps.find(bitmaps_path[bitmapsPathNumber]) == _bitmaps.end())
        _bitmaps[bitmaps_path[bitmapsPathNumber]] = al_load_bitmap(bitmaps_path[bitmapsPathNumber].c_str());

    return _bitmaps[bitmaps_path[bitmapsPathNumber]];
}
