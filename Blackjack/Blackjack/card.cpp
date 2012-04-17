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
	_outputFormat = "[ N - T ]";
}

Card::Card(CardSuit suit, CardName name, unsigned int score)
{
	_name = name;
	_suit = suit;
	SetScore(score);
	_outputFormat = "[ N - T ]";
}

std::string Card::GetFormattedName() const
{
	return "Chato!";
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