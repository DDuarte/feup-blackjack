#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include "s_game.h"

#include <string>
#include <vector>
#include <fstream>

class Card;
class RectButton;
union ALLEGRO_EVENT;

class Player
{
public:
    Player(std::ifstream& file, S_Game* game);

    std::string GetName() const { return _name; }
    double GetBalance() const { return _balance; }
    double IsDoubleBet() const { return _doubleBet; }
    Hand* GetHand() const { return _hand; }
    static std::string GetPlayersFileName() { return _playersFileName; }

    bool IsBusted() { return _hand->IsBusted(); }
    bool IsBlackjack() { return _hand->IsBlackjack(); }
    bool HasLost() { return _hand->IsBusted(); }

    void WriteText(std::ofstream& out) const;

    // In-game player actions
    void PlaceBet();
    bool Stand(RectButton* btn);
    bool Hit(RectButton* btn);
    bool Double(RectButton* btn);
    void Lose();
    void DealerBusts()  { _balance += (2*(S_Game::GetBet() * (1 + _doubleBet) )); }
    void WinsItAll()    { _balance += (3*(S_Game::GetBet() * (1 + _doubleBet) )); }
    void Wins()         { _balance += (S_Game::GetBet() * (1 + _doubleBet)); }
    void ResetPlayer();

    void NewCard(Card* card) { _hand->AddCard(card); }
    void ClearHand() { _hand->Clear(); }

    void Draw(bool activePlayer = false);

    void SetPosition(Vector2D position);
    bool IsPositionSet() { return _drawPosition.X != 0 && _drawPosition.Y != 0; }

private:
    bool ReadText(std::ifstream& in);

    std::string _name;
    double _balance;
    bool _doubleBet;

    static std::string _playersFileName;

    Hand* _hand;
    S_Game* _game;
    
    Vector2D _drawPosition;
};

#endif // PLAYER_H
