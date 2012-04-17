#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Player
{
public:
	Player();
	Player(std::string name, double balance, bet);

	std::string GetName() const { return _name; };
	double GetBalance() const { return _balance; };
	double GetBet() const { return _bet; };
	std::vector<Card> GetCards() const { return _cards; };

	void SetName(std::string name) { (name.size() > 0 ? _name = name : void); };
	void SetBalance(double balance) { _balance = balance; };
	bool Bet(double amount);	// Make a Bet.Returns true if player has money to bet amount or retuns false otherwise

private:
	std::string _name;
	double _balance;
	double _bet;
	std::vector<Card> _cards;
};

#endif // PLAYER_H
