#ifndef CARD_H
#define CARD_H

#include "utilities.h"
#include "utilitiesUI.h"

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


enum CardSuit
{
    CsNone = -1,
    Clubs,
    Spades,
    Hearts,
    Diamonds
};

enum CardName
{
    CnNone = -1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

//const std::string DEFAULT_OUTPUT_FORMAT = "[ N - S ]";
const TwoD::vector CARD_SIZE = TwoD::vector(73,98);

class Card
{
public:
    Card(CardSuit suit, CardName name, uint score, ALLEGRO_BITMAP *image);

    CardSuit GetSuit() const { return _suit; }
    CardName GetName() const { return _name; }
    uint GetScore() const { return _score; }
    float GetFrameWidth() const { return _frameSize.x; }
    float GetFrameHeight() const { return _frameSize.y; }

    //std::string GetFormattedName() const;

    //static std::string GetOutputFormat() { return _outputFormat; }

    //static void SetOutputFormat(std::string outputFormat) { _outputFormat = outputFormat; }

    bool IsValid() const { return _suit != CsNone && _name != CnNone && _score != 0; }

    void Draw(ALLEGRO_DISPLAY *display, float dx, float dy);
   
private:
    CardSuit _suit;
    CardName _name;
    uint _score;
    //static std::string _outputFormat; // [ N - T ]; { N - T }
    ALLEGRO_BITMAP *_image;
    TwoD::vector _frameSize;



};

#endif // CARD_H
