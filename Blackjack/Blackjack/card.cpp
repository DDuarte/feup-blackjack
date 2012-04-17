#include "card.h"
#include <string>
#include <stdexcept>
#include <sstream>

std::string Card::_outputFormat = DEFAULT_OUTPUT_FORMAT;

Card::Card()
{
	_name = CardName::CnNone;
	_suit = CardSuit::CsNone;
	_score = 0;
	_outputFormat = DEFAULT_OUTPUT_FORMAT;
}

Card::Card(CardSuit suit, CardName name, unsigned int score)
{
	_name = name;
	_suit = suit;
	SetScore(score);
	_outputFormat = DEFAULT_OUTPUT_FORMAT;
}

std::string Card::GetFormattedName() const
{
	if (!IsValid()) return "";
	std::string temp(_outputFormat);
	std::size_t pos = temp.find('N');
	switch (_name)
	{
	case CardName::Two:
		temp.replace(temp[pos], temp[pos+1], "Two");
		break;
	case CardName::Three:
		temp.replace(temp[pos], temp[pos+1], "Three");
		break;
	case CardName::Four:
		temp.replace(temp[pos], temp[pos+1], "Four");
		break;
	case CardName::Five:
		temp.replace(temp[pos], temp[pos+1], "Five");
		break;
	case CardName::Six:
		temp.replace(temp[pos], temp[pos+1], "Six");
		break;
	case CardName::Seven:
		temp.replace(temp[pos], temp[pos+1], "Seven");
		break;
	case CardName::Eight:
		temp.replace(temp[pos], temp[pos+1], "Eight");
		break;
	case CardName::Nine:
		temp.replace(temp[pos], temp[pos+1], "Nine");
		break;
	case CardName::Ten:
		temp.replace(temp[pos], temp[pos+1], "Ten");
		break;
	case CardName::Jack:
		temp.replace(temp[pos], temp[pos+1], "Jack");
		break;
	case CardName::Queen:
		temp.replace(temp[pos], temp[pos+1], "Queen");
		break;
	case CardName::King:
		temp.erase(temp.begin()+pos);
		temp.insert(pos, "King");
		break;
	case CardName::Ace:
		temp.erase(temp.begin()+pos);
		temp.insert(pos, "Ace");
		break;
	}
	
	pos = temp.find('S');
	switch (_suit)
	{
	case CardSuit::Clubs:
		temp.erase(temp.begin()+pos);
		temp.insert(pos, "Clubs");
		break;
	case CardSuit::Spades:
		temp.replace(temp[pos], temp[pos+1], "Spades");
		break;
	case CardSuit::Hearts:
		temp.replace(temp[pos], temp[pos+1], "Hearts");
		break;
	case CardSuit::Diamonds:
		temp.replace(temp[pos], temp[pos+1], "Diamonds");
		break;
	}
	return temp;
}

void Card::SetScore(unsigned int score)
{
	if (score >= MIN_SCORE && score <= MAX_SCORE) 
		_score = score;
	else
	{
		throw std::logic_error( "Invalid Score!" );

	}
}