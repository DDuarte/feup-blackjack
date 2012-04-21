#include <allegro5/allegro.h>
#include "card.h"

#include "blackjackUI.h"

int main()
{
    if (!al_init())
        Error("Failed to initialize Allegro.");

    BlackJackUI();

    return EXIT_SUCCESS;                                                       // exit
}
