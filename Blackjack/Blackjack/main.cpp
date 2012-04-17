#include "card.h"

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>

#include "localization.h"

#define GetStr(name) Localization::Instance()->GetString(name)

void CardTests()
{
    std::ofstream logFile("log.txt");

    std::clog.set_rdbuf(logFile.rdbuf());

    try
    {
        Card myCard(Clubs, Ace, 10);
        myCard.SetOutputFormat("{ N - S }");
        std::cout << myCard.GetFormattedName() << std::endl;
    }
    catch (std::logic_error &e)
    {
        std::clog << e.what() << std::endl;
    }
}

    loc.SetLang(loc.GetAvailableLanguages()[1]);
void Tests()
{
    CardTests();
}

int main()
{
    Localization::Instance()->SetLang(English); // default lang

    Tests();

    system("PAUSE");
    return EXIT_SUCCESS;
}
