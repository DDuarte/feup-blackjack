#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <vector>
#include <string>

namespace Localization
{
    static std::vector<std::string> ReadLangFile(char* lang);
    static char** FindLangs();
}

#endif // LOCALIZATION_H