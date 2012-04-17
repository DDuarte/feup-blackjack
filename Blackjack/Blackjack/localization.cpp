#include "localization.h"
#include <fstream>

namespace Localization
{
    std::vector<std::string> ReadLangFile(char* lang)
    {
        std::string filename = std::string(lang) + ".lang";
        std::ofstream file(filename, std::ios::app);

        if (!file.is_open())
            ; // TODO do something

        std::vector<std::string> strings;

        while (file.good())
        {
            std::string phrase;
            file << phrase;

            strings.push_back(phrase);
        }

        return strings;
    }

    char** FindLangs()
    {
        ; // TODO implement
    }
}