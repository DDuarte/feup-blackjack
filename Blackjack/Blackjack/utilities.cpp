#include "utilities.h"

#include <string>
#include <fstream>

namespace Utilities
{
    bool FileExists(std::string fileName)
    {
        std::ifstream in(fileName.c_str());

        if (in.is_open())
        {
            in.close();
            return true;
        }

        return false;
    }
}


