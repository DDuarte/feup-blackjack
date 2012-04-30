#ifndef ALLEGRO_OBJECT_H
#define ALLEGRO_OBJECT_H

union ALLEGRO_EVENT;

class AllegroObject
{
public:
    AllegroObject() { }

    virtual void Draw() = 0;
    virtual bool Update(ALLEGRO_EVENT* ev) = 0;
};

#endif // ALLEGRO_OBJECT_H
