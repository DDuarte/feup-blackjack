#ifndef UTILITIES_H
#define UTILITIES_H

typedef unsigned int uint;

struct Vector2D
{
    float X;
    float Y;
    Vector2D(float x, float y)
    {
        X = x;
        Y = y;
    }
};

void Error(char const* message);

#endif // UTILITIESUI_H