/*!
 * \file utilities.cpp
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#include "utilities.h"

#include <allegro5/allegro_native_dialog.h>

void Error(char const* message)
{
    al_show_native_message_box(NULL, "Error", message, NULL, NULL, ALLEGRO_MESSAGEBOX_ERROR);
    exit(EXIT_FAILURE);
}
