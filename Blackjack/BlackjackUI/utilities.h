/*!
 * \file utilities.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <sstream>
#include <iomanip>

//! Helper typedef for unsigned integers
typedef unsigned int uint;

/*!
 * \struct Vector2D
 *
 * \brief Represents a pair of floats (vector)
 *
 */
struct Vector2D
{
    //! X coordinate
    float X;
    //! Y coordinate
    float Y;
    //! Constructor
    Vector2D(float x, float y)
    {
        X = x;
        Y = y;
    }
    //! Constructor
    Vector2D()
    {
        X = 0;
        Y = 0;
    }
};

//! Shows a dialog box with error message
void Error(char const* message);

//! Converts any type to a string
template <typename T>
std::string ToString(T val)
{
    std::ostringstream out;
    out << val;

    return out.str();
}

//! Special case for double to string conversion
template <>
inline std::string ToString<double>(double val)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) <<val;
    return out.str();
}

#endif // UTILITIESUI_H
