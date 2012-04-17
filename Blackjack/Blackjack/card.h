#ifndef CARD_H
#define CARD_H

#include <string>

enum CardSuit
{
    None = -1,
    Clubs,
    Spades,
    Hearts,
    Diamonds
};

enum CardName
{
    None = -1,
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

class Card
{
public:
    Card();
    Card(CardSuit suit, CardName name, unsigned int score);
    CardSuit GetSuit() const { return _suit; }
    CardName GetName() const { return _name; };
    unsigned int GetScore() const { return _score };
    std::string GetFormattedName() const;
    bool IsValid() const { return _suit != None && _name != None && _score != -1; }

private:
	CardSuit _suit;
	CardName _name;
	unsigned int _score;
};

#endif // CARD_H
