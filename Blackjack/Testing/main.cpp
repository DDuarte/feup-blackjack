#include "../Blackjack/blackjack.h"
#include <iostream>
#include <stdexcept>
#include <exception>

int main()
{
    try
    {
        BlackJack game;
        std::cout << game.CanStart() << std::endl;

        std::cout << game.CanStart() << std::endl;

    }
    catch (std::exception* e)
    {
    	std::cout << e->what() << std::endl;
    }
    
    

    system("PAUSE");
}