#include "localization.h"

#include <fstream>
#include <cstring>
#include <stdio.h>
#include <iostream>

#ifndef _WIN32
#include <dirent.h>
#include <unistd.h>
#define GetCurrentDir getcwd
#else
#include "../Dep/dirent.h"
#include <direct.h>
#define GetCurrentDir _getcwd
#endif

Localization::Localization()
{
    _languages = std::vector<std::string>();
    _strings = std::vector<std::string>();

    FindLangs();
}

bool Localization::ReadLangFile(char* lang)
{
    std::string filename = std::string(lang) + ".lang";
    std::ifstream file(filename, std::ios::binary | std::ios::out);

    _strings.clear();

    if (!file.is_open())
        return false;

    while (!file.fail())
    {
        char phrase[200];
        file.getline(phrase, 200, '\0');

        if (*phrase != '\0') // not empty
            _strings.push_back(phrase);
    } 

    file.close();

    return true;
}

bool Localization::FindLangs()
{
    char* ext = ".lang";

    char currentPath[FILENAME_MAX];

    if (!GetCurrentDir(currentPath, sizeof(currentPath) / sizeof(TCHAR)))
        return false;

    DIR *dir;
    struct dirent *ent;
    dir = opendir(currentPath);
    if (dir != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
            if (strstr(ent->d_name, ext))
                _languages.push_back(std::string(ent->d_name).substr(0, 2));
        closedir(dir);
    }
    else
        return false;

    return true;
}

std::string Localization::GetString(Strings index) const
{
    if (_strings.size() > (unsigned)index)
        return _strings[index];
    else
        return std::string();
}

std::vector<Language> Localization::GetAvailableLanguages() const
{
    std::vector<Language> result;

    // TODO: Use LanguageShort[]
    for (size_t i = 0; i < _languages.size(); ++i)
    {
        if (_languages[i] == "en")
            result.push_back(English);
        else if (_languages[i] == "pt")
            result.push_back(Portuguese);
        else if (_languages[i] == "es")
            result.push_back(Spanish);
        else if (_languages[i] == "fr")
            result.push_back(French);
        else
            result.push_back(None);
    }

    return result;
}

void Localization::SetLang(Language lang)
{
    _currLang = lang;
    ReadLangFile(LanguageShort[_currLang]);
}
