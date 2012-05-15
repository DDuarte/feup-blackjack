#include "localization.h"

#include <fstream>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <exception>

#ifndef _WIN32
#include <dirent.h>
#include <unistd.h>
#define GetCurrentDir getcwd
#else
#include "../Dep/dirent.h"
#include <direct.h>
#define GetCurrentDir _getcwd
#endif

Localization* Localization::_instance = NULL;

Localization* Localization::Instance()
{
    if (!_instance)
        _instance = new Localization;

    return _instance;
}

Localization::Localization()
{
    _languages = std::vector<Language>();
    _strings = std::vector<std::string>();

    FindLangs();
}

bool Localization::ReadLangFile(char* lang)
{
    std::string filename = std::string(lang) + ".lang";
    std::ifstream file(filename, std::ios::binary);

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
    std::string ext = ".lang";

    char currentPath[FILENAME_MAX];

    if (!GetCurrentDir(currentPath, sizeof(currentPath) / sizeof(TCHAR)))
        return false;

    DIR *dir;
    struct dirent *ent;
    dir = opendir(currentPath);
    if (dir != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            std::string fileName = ent->d_name;
            if (fileName.size() > (ext.size() + 1) && fileName.substr(fileName.size() - ext.size(), ext.size()) == ext)
                _languages.push_back(GetLanguageByShortLang(fileName.substr(0, 2)));
        }

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

void Localization::SetLang(Language lang)
{
    if (std::find(_languages.begin(), _languages.end(), lang) != _languages.end())
    {
        _currLang = lang;
        ReadLangFile(LanguageShort[_currLang]);
    }
    else
    {
        std::ostringstream ss;
        ss << "Language " << lang << " was not found.";
        throw std::exception(ss.str().c_str());
    }

}

Language Localization::GetLanguageByShortLang(std::string lang)
{
    if (lang == "en") return LANGUAGE_ENGLISH;
    else if (lang == "pt") return LANGUAGE_PORTUGUESE;
    else if (lang == "es") return LANGUAGE_SPANISH;
    else if (lang == "fr") return LANGUAGE_FRENCH;
    else                   return LANGUAGE_NONE;
}
