#include "card.h"
#include "localization.h"
#include "gameExceptions.h"

#include <string>
#include <stdexcept>
#include <sstream>

std::string Card::_outputFormat = DEFAULT_OUTPUT_FORMAT;

Card::Card()
{
    _name = CnNone;
    _suit = CsNone;
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
    if (!IsValid()) throw InvalidCardException("Invalid card exception at Card::GetFormattedName()!");
    std::string temp(_outputFormat);

    std::size_t pos = temp.find('N');
    temp.erase(temp.begin()+pos);
    temp.insert(pos, GetStr((Strings)(_name + STR_NAMES + 1)));
    
    pos = temp.find('S');
    temp.erase(temp.begin()+pos);
    temp.insert(pos, GetStr((Strings)(_suit + STR_SUITS + 1)));

    return temp;
}

void Card::SetScore(unsigned int score)
{
    if (score >= MIN_SCORE && score <= MAX_SCORE) 
        _score = score;
    else
    {
        throw InvalidScoreException( "Invalid card score at Card::SetScore(unsigned int score)!" );

    }
}
