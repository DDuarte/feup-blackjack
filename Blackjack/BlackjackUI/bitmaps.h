#ifndef BITMAPS_H
#define BITMAPS_H

#include "utilities.h"

#include <map>
#include <vector>
#include <string>

struct ALLEGRO_BITMAP;

enum bitmaps
{
    BITMAP_MENU_BACKGROUND,
    BITMAP_GAME_BACKGROUND,
    BITMAP_GAME_CHIP,
    BITMAP_GAME_CARDS_SPRITE,
    BITMAP_GAME_CARDS_BACK_SPRITE
};

static std::string bitmaps_path[] = 
{
    "../../Resources/wallpaper.jpg", 
    "../../Resources/playing_table.png", 
    "../../Resources/chip1.png",
    "../../Resources/Sprites/card_sprites.png", 
    "../../Resources/cards/b1fv.png"
};

class Bitmaps
{
public:
    static void UnloadBitmaps();
    static ALLEGRO_BITMAP* GetBitmap(int bitmaps_path_number);

private:
    static std::map<std::string, ALLEGRO_BITMAP*> _bitmaps;
    
};

#endif // BITMAPS_H