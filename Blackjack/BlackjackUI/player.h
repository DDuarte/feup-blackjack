/*!
 * \file player.h
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include "utilities.h"
#include "bitmap.h"

#include <string>
#include <vector>
#include <fstream>

class Card;
class RectButton;
union ALLEGRO_EVENT;
class S_Game;

const Vector2D PLAYER_POSITIONS[]  = 
{
    Vector2D(652, 217),
    Vector2D(460, 344),
    Vector2D(260, 344),
    Vector2D(82, 217)
};

/*!
 * \class Player
 *
 * \brief Represents a player
 *
 */
class Player
{
public:
    //! Constructor. Reads "balance(space)name" from a file
    Player(std::ifstream& file, S_Game* game);
    //! Saves a player to a file
    void Save(std::ofstream& out) const;

    //! Name
    std::string GetName() const { return _name; }
    //! Current balance
    double GetBalance() const { return _balance; }
    //! Initial balance
    double GetInitialBalance() const { return _initialBalance; }
    //! Difference between current balance and initial balance
    double GetBalanceDiff() const { return _balance - _initialBalance; }
    //! True if player did a double bet
    double IsDoubleBet() const { return _doubleBet; }
    //! Player's hand score
    uint GetScore() const { return _hand->GetScore(); }

    //! Name of the file that is used to read/save players (players.txt by default)
    static std::string GetPlayersFileName() { return _playersFileName; }

    //! Increases player's balance by inc amount (can be negative)
    void IncreaseBalance(double inc) { _balance += inc; }

    //! True if player is busted
    bool IsBusted() const { return _hand->IsBusted(); }
    //! True if player got blackjack
    bool IsBlackjack() const { return _hand->IsBlackjack(); }
    //! True if player can double
    bool CanDouble() const { return (_hand->GetScore() == 9 || _hand->GetScore() == 10 || _hand->GetScore() == 11) && _hand->GetNumberOfCards() == 2; }

    //! True if player has lost current round
    bool HasLost() const { return _hand->IsBusted(); }

    //! Player enters the game
    void EnterGame(int index);

    // In-game player actions
    //! Player does a bet
    void PlaceBet();
    //! Player stands
    bool Stand(RectButton* btn);
    //! Player hits
    bool Hit(RectButton* btn);
    //! Player doubles
    bool Double(RectButton* btn);
    //! Player surrenders
    bool Surrender(RectButton* btn);
    //! Player stays in-game
    bool Stay(RectButton* btn);

    //! True if player accepted surrender (asked in end of round)
    bool WantsSurrender() const { return _surrender; }

    //! Resets player for a new round
    void ResetPlayer();

    // Hand
    //! Adds a new card to player's hand
    void NewCard(Card* card) { _hand->AddCard(card); }
    //! Removes all cards from player's hand
    void ClearHand() { _hand->Clear(); }

    //! Draw player name, bet, balance and hand to screen
    void Draw(bool activePlayer = false);

private:
    bool ReadText(std::ifstream& in);

    std::string _name;
    double _balance;
    double _initialBalance;

    bool _doubleBet;

    static std::string _playersFileName;

    Hand* _hand;
    S_Game* _game;

    int _index;

    bool _surrender;

    Bitmap _chip;
    Bitmap _doubleChip;

};

#endif // PLAYER_H
