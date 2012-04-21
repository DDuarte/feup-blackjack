#include "utilities.h"

#include <allegro5/allegro_native_dialog.h>

void Error(char const* message)
{
    al_show_native_message_box(NULL, "Error", NULL, message, NULL, ALLEGRO_MESSAGEBOX_ERROR);
    exit(EXIT_FAILURE);
}
