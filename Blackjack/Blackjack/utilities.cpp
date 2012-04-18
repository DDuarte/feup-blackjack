#include "utilities.h"

#include <string>
#include <fstream>

namespace Utilities
{
    bool FileExists(std::string fileName)
    {
        std::ifstream in(fileName.c_str());
        return in.is_open();
    }
}


