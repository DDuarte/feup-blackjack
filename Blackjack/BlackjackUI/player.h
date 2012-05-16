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

class Player
{
public:
    Player(std::ifstream& file, S_Game* game);
    void Save(std::ofstream& out) const;
    ~Player() { /*delete _hand;*/ }

    std::string GetName() const { return _name; }
    double GetBalance() const { return _balance; }
    double GetInitialBalance() const { return _initialBalance; }
    double GetBalanceDiff() const { return _balance - _initialBalance; }
    double IsDoubleBet() const { return _doubleBet; }
    uint GetScore() const { return _hand->GetScore(); }
    static std::string GetPlayersFileName() { return _playersFileName; }

    void IncreaseBalance(double inc) { _balance += inc; }

    bool IsBusted() const { return _hand->IsBusted(); }
    bool IsBlackjack() const { return _hand->IsBlackjack(); }
    bool CanDouble() const { return (_hand->GetScore() == 9 || _hand->GetScore() == 10 || _hand->GetScore() == 11) && _hand->GetNumberOfCards() == 2; }

    bool HasLost() const { return _hand->IsBusted(); }

    void EnterGame(int index);

    // In-game player actions
    void PlaceBet();
    bool Stand(RectButton* btn);
    bool Hit(RectButton* btn);
    bool Double(RectButton* btn);
    bool Surrender(RectButton* btn);
    bool Stay(RectButton* btn);

    bool WantsSurrender() const { return _surrender; }

    void ResetPlayer();

    // Hand
    void NewCard(Card* card) { _hand->AddCard(card); }
    void ClearHand() { _hand->Clear(); }

    // Drawing
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
