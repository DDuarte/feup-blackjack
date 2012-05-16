#ifndef BITMAPS_H
#define BITMAPS_H

#include "utilities.h"

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
    "../../Resources/Sprites/wallpaper.jpg", 
    "../../Resources/Sprites/playing_table.png", 
    "../../Resources/Sprites/chip1.png",
    "../../Resources/Sprites/card_sprites.png", 
    "../../Resources/Sprites/b1fv.png",
    "../../Resources/Sprites/gameoverscreen.png"
};

class Bitmaps
{
public:
    static void UnloadBitmaps();
    static ALLEGRO_BITMAP* GetBitmap(int bitmapsPathNumber);

private:
    static std::map<std::string, ALLEGRO_BITMAP*> _bitmaps;
    
};

#endif // BITMAPS_H