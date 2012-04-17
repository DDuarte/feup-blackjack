#include <fstream>
#include <iostream>
#include <string>

// .__ .___.  ..___.   .__..__ .___.__   .  . __..___  .__..  ..   .   ,  //
// |  \[__ \  /[__ |   |  |[__)[__ [__)  |  |(__ [__   |  ||\ ||    \./   //
// |__/[___ \/ [___|___|__||   [___|  \  |__|.__)[___  |__|| \||___  |    //

int main()
{
    std::cout << "** BinaryCardMaker" << std::endl << std::endl;

    std::cout << "A) Build base (English)" << std::endl;
    std::cout << "B) Build custom" << std::endl;
    std::cout << "C) Build Portuguese" << std::endl;
    // std::cout << "D) Build French" << std::endl;

    char ans;
    std::cin >> ans;

    struct Language
    {
        std::string Phrases[3];
    };

    Language strings[] =
    {   //  en           pt
        { "Suits"   , "Naipes" },
        { "Clubs"   , "Paus" },
        { "Spades"  , "Espadas"},
        { "Hearts"  , "Copas" },
        { "Diamonds", "Ouros" },
        { "Names"   , "Nomes" },
        { "Two"     , "Dois" },
        { "Three"   , "Tres" },
        { "Four"    , "Quatro" },
        { "Five"    , "Cinco" },
        { "Six"     , "Seis" },
        { "Seven"   , "Sete" },
        { "Eight"   , "Oito" },
        { "Nine"    , "Nove" },
        { "Ten"     , "Dez" },
        { "Jack"    , "Valete" },
        { "Queen"   , "Dama" },
        { "King"    , "Rei" },
        { "Ace"     , "Ás" },
    };

    const int count = 19;

    std::string lang;

    int langIndex;

    switch (ans)
    {
        case 'A': lang = "en"; langIndex = 0; break;
        case 'C': lang = "pt"; langIndex = 1; break;
        case 'B':
        {
            std::cout << "Note: type x to skip word" << std::endl;

            std::cout << "Lang (2 chars, lowercase): ";
            std::cin >> lang;

            for (size_t i = 0; i < count; ++i)
            {
                std::cout << strings[i].Phrases[0] << ": ";

                std::string newLocal;
                std::cin >> newLocal;

                if (newLocal == "x")
                    continue;

                strings[i].Phrases[2] = newLocal;
            }

            langIndex = 2;
            break;
        }
        default:
            exit(EXIT_FAILURE);
    }

    // Write file
    std::string filename = lang + ".lang";
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
        exit(EXIT_FAILURE);

    for (size_t i = 0; i < count; ++i)
        file << strings[i].Phrases[langIndex] << '\0';

    std::cout << "Success";
    std::getchar();

    return EXIT_SUCCESS;
}
