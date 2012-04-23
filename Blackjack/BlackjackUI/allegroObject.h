#ifndef ALLEGROOBJECT_H
#define ALLEGROOBJECT_H

class AllegroObject
{
public:
    virtual void Initialize();
    virtual void LoadContents();
    virtual void Draw();
    virtual void Update();
    virtual void UnloadContents();
private:
};

#endif // ALLEGROOBJECT_H