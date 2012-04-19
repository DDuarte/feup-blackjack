#include "card.h"

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <ctime>

#include "utilities.h"
#include "localization.h"
#include "deck.h"
#include "gameExceptions.h"

void CardTests()
{
    std::ofstream logFile("log.txt", std::ios::app);
    std::clog.set_rdbuf(logFile.rdbuf());

    std::clog << std::endl;

    try
    {
        Card myCard(Clubs, Ace, 10);
        myCard.SetOutputFormat("{ N - S }");
        std::cout << myCard.GetFormattedName() << std::endl;
    }
    catch (InvalidCardException &e)
    {
        std::clog << e.what() << std::endl;
    }
    catch (InvalidScoreException &e)
    {
        std::clog << e.what() << std::endl;
    }

    std::clog << std::endl;
    logFile.close();
}

void DeckTests()
{
    Deck d;
}

void Tests()
{
    DeckTests();
    CardTests();
}

int main()
{
    Localization::Instance()->SetLang(English); // default lang
    srand((uint)time(NULL)); // initialize seed

    Tests();

    system("PAUSE");
    return EXIT_SUCCESS;
}
