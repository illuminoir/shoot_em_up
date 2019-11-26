#ifndef __GAME__
#define __GAME__

#include "../include/collisions.h"
#include "../include/display_game.h"
#include <time.h>
#include <MLV/MLV_all.h>


#define BILLION 1000000000

int get_ship_event(MLV_Keyboard_button key, MLV_Button_state state, int* x, int* y);

void main_loop(Ship* ship, Stars* stars);

#endif