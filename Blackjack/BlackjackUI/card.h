/*!
 * \file card.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

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

/*!
 * \class Card
 *
 * \brief Defines a playing card
 *
 */
class Card
{
public:
    //! Constructor
    Card(int suit, int rank);

    //! Suit of the card (clubs, spades, hearts and diamonds)
    int GetSuit() const { return _suit; }
    //! Type of the card (ace, two, three, ...)
    int GetRank() const { return _rank; }
    //! Score
    uint GetScore() const { return _score; }
    //! Width of the card
    float GetFrameWidth() const { return _frameSize.X; }
    //! Height of the card
    float GetFrameHeight() const { return _frameSize.Y; }
    //! Text representation of the card in the format [S - R]
    std::string GetName() const;

    //! Changes score of the card; should only be used with aces
    void SetScore(int score) { if (_rank == CARD_RANK_ACE) _score = score; }

    //! Returns the position the card is being draw
    Vector2D GetPosition() { return _bitmap.GetDestinationCoordinates(); }
    //! Changes the position the card is being draw
    void SetPosition(Vector2D val) { _bitmap.SetDestinationCoordinates(val); }

    //! Returns true if the card is valid
    bool IsValid() const { return _suit != -1 && _rank != -1 && _score != -1; }

    //! Draws the card to the screen
    void Draw(float angle = 0.0, bool mouseHovered = false, bool drawBack = false); // angle must be in radians

private:
    int _suit;
    int _rank;
    uint _score;

    Bitmap _bitmap;

    int _backColorRGB;

    static Vector2D _frameSize;
};

#endif // CARD_H
