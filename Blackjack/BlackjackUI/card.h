#ifndef CARD_H
#define CARD_H

#include "utilities.h"
#include "bitmap.h"

#include <string>

enum CardSuit
{
    CARD_SUIT_CLUBS,
    CARD_SUIT_SPADES,
    CARD_SUIT_HEARTS,
    CARD_SUIT_DIAMONDS
};

enum CardRank
{
    CARD_RANK_TWO,
    CARD_RANK_THREE,
    CARD_RANK_FOUR,
    CARD_RANK_FIVE,
    CARD_RANK_SIX,
    CARD_RANK_SEVEN,
    CARD_RANK_EIGHT,
    CARD_RANK_NINE,
    CARD_RANK_TEN,
    CARD_RANK_JACK,
    CARD_RANK_QUEEN,
    CARD_RANK_KING,
    CARD_RANK_ACE
};

const Vector2D CARD_SIZE = Vector2D(73, 98);

// by rank
const uint SCORES[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 10, 11 };

struct ALLEGRO_BITMAP;
struct ALLEGRO_DISPLAY;

class Card
{

public:
    Card(int suit, int rank);

    int GetSuit() const { return _suit; }
    int GetRank() const { return _rank; }
    uint GetScore() const { return _score; }
    float GetFrameWidth() const { return _frameSize.X; }
    float GetFrameHeight() const { return _frameSize.Y; }
    std::string GetName() const;;

    void SetScore(int score) { if (_rank == CARD_RANK_ACE) _score = score; }

    Vector2D GetPosition() { return _BMP.GetDestinationCoordinates(); }
    void SetPosition(Vector2D val) { _BMP.SetDestinationCoordinates(val); }

    bool IsValid() const { return _suit != -1 && _rank != -1 && _score != -1; }

    void Draw(float angle = 0.0, bool mouseHovered = false, bool drawBack = false); // angle must be in radians

    static void DestroyBitmaps();

private:
    int _suit;
    int _rank;
    uint _score;

    Bitmap _BMP;

    int _backColorRGB;

    static ALLEGRO_BITMAP* _image;
    static ALLEGRO_BITMAP* _backImage;
    static Vector2D _frameSize;
};

#endif // CARD_H
