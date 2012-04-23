#ifndef FONTS_H
#define FONTS_H

struct ALLEGRO_FONT;

class Fonts
{
public:
    static void LoadFonts();
    static void UnloadFonts();

    static ALLEGRO_FONT* GetFont10() { return _font10; }
    static ALLEGRO_FONT* GetFont50() { return _font50; }
    static ALLEGRO_FONT* GetFont140() { return _font140; }
    
private:
    static ALLEGRO_FONT* _font10;
    static ALLEGRO_FONT* _font50;
    static ALLEGRO_FONT* _font140;
};

#endif // FONTS_H
