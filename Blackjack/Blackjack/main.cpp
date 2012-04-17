#include "card.h"
#include <iostream>
#include <stdexcept>
#include <fstream>

int main()
{
	std::ofstream logFile("log.txt");

	std::clog.set_rdbuf(logFile.rdbuf());

	try
	{
		Card myCard(CardSuit::Clubs, CardName::Ace, 10);
		std::cout << myCard.GetFormattedName() << std::endl;
	}
	catch (std::logic_error &e)
	{
		std::clog << e.what() << std::endl;
	}

	

	system("PAUSE");

	return 0;
}