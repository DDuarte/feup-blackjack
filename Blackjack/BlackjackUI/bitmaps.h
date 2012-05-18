/*!
 * \file bitmaps.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 *
 */

#ifndef BITMAPS_H
#define BITMAPS_H

#include <map>
#include <vector>
#include <string>

struct ALLEGRO_BITMAP;

enum BitmapsEnum
{
    BITMAP_MENU_BACKGROUND,
    BITMAP_GAME_BACKGROUND,
    BITMAP_GAME_CHIP,
    BITMAP_GAME_CARDS_SPRITE,
    BITMAP_GAME_CARDS_BACK_SPRITE,
    BITMAP_MENU_GAME_OVER,
};

static std::string bitmaps_path[] = 
{
    "res/wallpaper.jpg", 
    "res/playing_table.png", 
    "res/chip1.png",
    "res/card_sprites.png", 
    "res/b1fv.png",
    "res/gameoverscreen.png"
};

/*!
 * \class Bitmaps
 *
 * \brief Represents a set of ALLEGRO_BITMAP
 *
 */
class Bitmaps
{
public:
    //! Releases memory used by all bitmaps
    static void UnloadBitmaps();
    //! Returns an ALLEGRO_BITMAP (BitmapsEnum)
    static ALLEGRO_BITMAP* GetBitmap(int bitmapsPathNumber);

private:
    static std::map<std::string, ALLEGRO_BITMAP*> _bitmaps;
    
};

#endif // BITMAPS_H