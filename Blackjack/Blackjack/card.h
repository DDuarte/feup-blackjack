#ifndef CARD_H
#define CARD_H

#include "utilities.h"
#include <string>

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

const std::string DEFAULT_OUTPUT_FORMAT = "[ N - S ]";

class Card
{
public:
    Card(CardSuit suit, CardName name, uint score);

    CardSuit GetSuit() const { return _suit; }
    CardName GetName() const { return _name; }
    uint GetScore() const { return _score; }
    std::string GetFormattedName() const;
    static std::string GetOutputFormat() { return _outputFormat; }

    static void SetOutputFormat(std::string outputFormat) { _outputFormat = outputFormat; }

    bool IsValid() const { return _suit != CsNone && _name != CnNone && _score != 0; }

private:
    CardSuit _suit;
    CardName _name;
    uint _score;
    static std::string _outputFormat; // [ N - T ]; { N - T }
};

#endif // CARD_H
