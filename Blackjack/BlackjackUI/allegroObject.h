#ifndef ALLEGROOBJECT_H
#define ALLEGROOBJECT_H

#include <allegro5/allegro.h>

class AllegroObject
{
public:
    AllegroObject() {};

    virtual void Draw() { }
    virtual bool Update(ALLEGRO_EVENT* ev){ return true; }

private:
};

#endif // ALLEGROOBJECT_H