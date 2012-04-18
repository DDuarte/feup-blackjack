#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>

namespace Utilities
{
    // Swaps two values
    template<typename T>
    void Swap(T& val1, T& val2)
    {
        T temp = val1;
        val1 = val2;
        val2 = temp;
    }

    bool FileExists(std::string fileName);
}

#endif // UTILITIES_H_
