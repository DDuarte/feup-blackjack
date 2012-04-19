#include "../Blackjack/blackjack.h"
#include <iostream>
#include <stdexcept>
#include <exception>

int main()
{
    try
    {
        BlackJack game;
        std::cout << "Number of players registered: " << game.RegisteredPlayerCount() << std::endl;
        std::cout << "Number of players waiting: " << game.WaitingPlayerCount() << std::endl;
        std::cout << "Number of players playing: " << game.ActivePlayerCount() << std::endl;

        std::cout << "Starting game..." << std::endl;
        game.Start();

        std::cout << "Number of players registered: " << game.RegisteredPlayerCount() << std::endl;
        std::cout << "Number of players waiting: " << game.WaitingPlayerCount() << std::endl;
        std::cout << "Number of players playing: " << game.ActivePlayerCount() << std::endl;

    }
    catch (std::exception* e)
    {
    	std::cout << e->what() << std::endl;
    }
    
    

    system("PAUSE");
}