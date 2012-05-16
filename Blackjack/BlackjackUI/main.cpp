#include <allegro5/allegro.h>

#include "blackjack.h"
#include "localization.h"

int main()
{
    if (!al_init())
        Error("Failed to initialize Allegro.");

    Localization::Instance()->SetLang(LANGUAGE_ENGLISH);
    BlackJack::Instance()->_Start();

    return EXIT_SUCCESS;
}
