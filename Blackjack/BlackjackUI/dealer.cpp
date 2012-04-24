#include "s_game.h"
#include "dealer.h"


Dealer::Dealer(S_Game* game)
{
    _game = game;
    _hand = Hand(/*true*/);
}

void Dealer::Hit()
{
    Card* tempCard = _game->GetDeck()->WithdrawCard();

    if (tempCard != NULL)
    {
        _hand.AddCard(tempCard);
        _game->DealerHit(this);
    }
    else
        _game->HandleOutOfCards();
}

void Dealer::Stand()
{
    _game->DealerHit(this);
}
