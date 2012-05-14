#include <fstream>
#include <iostream>
#include <string>

#include <windows.h>

// .__ .___.  ..___.   .__..__ .___.__   .  . __..___  .__..  ..   .   ,  //
// |  \[__ \  /[__ |   |  |[__)[__ [__)  |  |(__ [__   |  ||\ ||    \./   //
// |__/[___ \/ [___|___|__||   [___|  \  |__|.__)[___  |__|| \||___  |    //

// by Jere.Jones (http://codereview.stackexchange.com/questions/419/converting-between-stdwstring-and-stdstring)
std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    std::wstring r(len, L'\0');
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, &r[0], len);
    return r;
}

// by Marius Bancila (http://mariusbancila.ro/blog/2008/10/20/writing-utf-8-files-in-c/)
std::string to_utf8(const wchar_t* buffer, int len)
{
    int nChars = ::WideCharToMultiByte(CP_UTF8, 0, buffer, len, NULL, 0, NULL, NULL);
    if (nChars == 0)
        return "";

    std::string newbuffer;
    newbuffer.resize(nChars);
    ::WideCharToMultiByte(CP_UTF8, 0, buffer, len, const_cast< char* >(newbuffer.c_str()), nChars, NULL, NULL); 

    return newbuffer;
}

// by Marius Bancila (http://mariusbancila.ro/blog/2008/10/20/writing-utf-8-files-in-c/)
std::string to_utf8(const std::wstring& str)
{
    return to_utf8(str.c_str(), (int)str.size());
}

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
        { "Play"    , "Jogar" },
        { "Options" , "Opções" },
        { "Quit"    , "Sair" },
        { "Hit"     , "Pedir" },
        { "Stand"   , "Ficar" },
        { "Double"  , "Dobrar" },
        { "Give Up" , "Desistir" },
        { "Stay"    , "Ficar" }
    };

    const int count = sizeof(strings) / sizeof(strings[0]);

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
        file << to_utf8(s2ws(strings[i].Phrases[langIndex]));

    file.close();

    std::cout << "Success";
    std::getchar();

    return EXIT_SUCCESS;
}
