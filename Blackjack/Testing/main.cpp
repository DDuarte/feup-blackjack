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

        game.RegisterPlayer("Duarte", 100);
        game.RegisterPlayer("Miguel", 100);
        game.RegisterPlayer("O outro", 100);
        game.RegisterPlayer("A outra", 100);

        std::cout << game.CanStart() << std::endl;

    }
    catch (std::exception* e)
    {
    	std::cout << e->what() << std::endl;
    }
    
    

    system("PAUSE");
}