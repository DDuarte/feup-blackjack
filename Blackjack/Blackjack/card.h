#ifndef CARD_H
#define CARD_H

enum CardSuit { Clubs, Spades, Hearts, Diamonds };
enum CardName { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

class Card
{
public:

private:
	CardSuit _suit;
	CardName _name;
	int _score;

};

#endif // CARD_H