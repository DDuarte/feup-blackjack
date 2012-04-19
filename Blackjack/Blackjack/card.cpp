#include "utilities.h"
#include "card.h"
#include "localization.h"
#include "gameExceptions.h"

#include <string>
#include <sstream>

std::string Card::_outputFormat = DEFAULT_OUTPUT_FORMAT;

Card::Card(CardSuit suit, CardName name, uint score) : _name(name), _suit(suit), _score(score) { }

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
