#include <allegro5/allegro.h>
#include "card.h"

#include "blackjack.h"

int main()
{
    if (!al_init())
        Error("Failed to initialize Allegro.");

    BlackJack::Instance()->_Start();

    return EXIT_SUCCESS;
}
