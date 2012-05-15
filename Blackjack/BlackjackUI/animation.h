#ifndef ANIMATION_H
#define ANIMATION_H

#include "bitmap.h"

#include <vector>

class Animation
{
	public:
        virtual void Initialize() = 0;
        virtual void LoadContents() = 0;
        virtual bool Update() = 0;
        virtual void Draw() = 0;
        virtual void UnloadContents() = 0;
	protected:
        Animation();
        //~Animation();        
};

class ZoomAnimation : public Animation
{
    public:
        ZoomAnimation() : Animation() { }

    private:
        Bitmap _bmp;

};

class SpriteAnimation : public Animation
{
    public:
        SpriteAnimation() : Animation() { }
};

#endif // ANIMATION_H
