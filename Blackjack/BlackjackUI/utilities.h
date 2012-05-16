#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <sstream>

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
    Vector2D()
    {
        X = 0;
        Y = 0;
    }
};

void Error(char const* message);

template <typename T>
std::string ToString(T val)
{
    std::ostringstream out;
    out << val;
    return out.str();
}

#endif // UTILITIESUI_H
