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

// Singleton since we need to use it all around the code
class Localization
{
public:
    static Localization* Inst();
    
    std::vector<Language> GetAvailableLanguages() const { return _languages; }

    std::string GetString(Strings index) const;
    std::string operator[] (const Strings index);

    void SetLang(Language lang);

private:
    Localization();

    static Localization* _instance;

    std::vector<Language> _languages;
    std::vector<std::string> _strings;
    Language _currLang;

    bool ReadLangFile(char* lang);
    bool FindLangs();
    static Language GetLanguageByShortLang(std::string lang);
};

#endif // LOCALIZATION_H
