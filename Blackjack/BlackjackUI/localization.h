#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <vector>
#include <string>

#define GetStr(name) Localization::Instance()->GetString((name))

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
    STR_PLAY,
    STR_OPTIONS,
    STR_QUIT,
    STR_HIT,
    STR_STAND,
    STR_DOUBLE,
    STR_GIVEUP,
    STR_STAY,
    STR_BUSTED,
    STR_STOOD,
    STR_EXIT,
    STR_SURE_EXIT,
    STR_PLAYER_HIT_F,
    STR_PLAYER_STAND_F,
    STR_PLAYER_DOUBLE_F,
    STR_DEALER_HIT_F,
    STR_STAT_WINNER_IS,
    STR_STAT_BETS,
    STR_STAT_ROUNDS,
    STR_STAT_HITS,
    STR_STAT_STANDS,
    STR_STAT_DOUBLES,
    STR_STAT_BJS,
    STR_STAT_BUSTS,
    STR_STAT_SPENT_MONEY,
    STR_STAT_RECEIVED_MONEY,
    STR_STAT_PLR_WON_MORE,
    STR_STAT_PLR_LOST_MORE,
    STR_STAT_PLR_HEADER,
    STR_SOUND,
    STR_ACTUAL_F,
    STR_BET,
    // more here
};

enum Language
{
    LANGUAGE_NONE,
    LANGUAGE_ENGLISH,
    LANGUAGE_PORTUGUESE,
    LANGUAGE_FRENCH,
    LANGUAGE_SPANISH
};

static char* LanguageShort[] = { "uk", "en", "pt", "fr", "es" };
static std::string LanguageComplete[] = { "Unknown", "English", "Português", "Français", "Español" };

// Singleton since we need to use it all around the code
// To get a string of the current language use the macro GetStr() and pass an element of the Strings element
class Localization
{
public:
    static Localization* Instance();

    std::vector<Language> GetAvailableLanguages() const { return _languages; }

    std::string GetString(Strings index) const;
    std::string GetCurrentLanguage() const;

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
