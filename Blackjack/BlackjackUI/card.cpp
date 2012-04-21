#include "utilities.h"
#include "card.h"
//#include "localization.h"
#include "gameExceptions.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


#include <string>
#include <sstream>

//std::string Card::_outputFormat = DEFAULT_OUTPUT_FORMAT;


Card::Card(CardSuit suit, CardName name, uint score, ALLEGRO_BITMAP *image) : _name(name), _suit(suit), _score(score), _image(image), _frameSize(CARD_SIZE) { }

//std::string Card::GetFormattedName() const
//{
//    if (!IsValid()) throw InvalidCardException("Invalid card exception at Card::GetFormattedName()!");
//    std::string temp(_outputFormat);
//
//    std::size_t pos = temp.find('N');
//    temp.erase(temp.begin()+pos);
//    temp.insert(pos, GetStr((Strings)(_name + STR_NAMES + 1)));
//    
//    pos = temp.find('S');
//    temp.erase(temp.begin()+pos);
//    temp.insert(pos, GetStr((Strings)(_suit + STR_SUITS + 1)));
//
//    return temp;
//}

void Card::Draw(ALLEGRO_DISPLAY *display, float dx, float dy)
{
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap_region(_image, _name * _frameSize.x , _suit * _frameSize.y, _frameSize.x, _frameSize.y, dx, dy, 0); 
}
