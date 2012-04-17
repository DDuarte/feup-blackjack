#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <vector>
#include <string>

enum Strings
{
    STR_SUITS,
    STR_CLUBS,
    STR_SPADES,
    STR_HEARTS,
    STR_DIAMONDS,
    STR_NAMES,
    STR_TWO,
    STR_THREE,
    STR_FOUR,
    STR_FIVE,
    STR_SIX,
    STR_SEVEN,
    STR_EIGHT,
    STR_NINE,
    STR_TEN,
    STR_JACK,
    STR_QUEEN,
    STR_KING,
    STR_ACE,
    // more here
};

enum Language
{
    None,
    English,
    Portuguese,
    French,
    Spanish
};

static char* LanguageShort[] = { "uk", "en", "pt", "fr", "es" };

class Localization
{
public:
    Localization();
    
    std::vector<Language> GetAvailableLanguages() const;
    std::string GetString(Strings index) const;
    void SetLang(Language lang);

private:
    std::vector<std::string> _languages;
    std::vector<std::string> _strings;
    Language _currLang;

    bool ReadLangFile(char* lang);
    bool FindLangs();
};

#endif // LOCALIZATION_H
