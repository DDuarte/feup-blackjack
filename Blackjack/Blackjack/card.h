#ifndef CARD_H
#define CARD_H

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

const std::string DEFAULT_OUTPUT_FORMAT = "[ N - T ]";
const unsigned int MAX_SCORE = 11;
const unsigned int MIN_SCORE = 0;

class Card
{
public:
    Card();
    Card(CardSuit suit, CardName name, unsigned int score);
    CardSuit GetSuit() const { return _suit; };
    CardName GetName() const { return _name; };
    unsigned int GetScore() const { return _score; };
    std::string GetFormattedName() const;
    bool IsValid() const { return _suit != CsNone && _name != CnNone && _score != 0; };
	static std::string GetOutputFormat() { return _outputFormat; };
	void SetScore(unsigned int score);
	//static std::string SetOutputFormat();

private:
	CardSuit _suit;
	CardName _name;
	unsigned int _score;
	static std::string _outputFormat; // [ N - T ]; { N - T }
};



#endif // CARD_H
