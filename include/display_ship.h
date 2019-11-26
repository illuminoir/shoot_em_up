#ifndef __DISPLAY_SHIP__
#define __DISPLAY_SHIP__

#include "../include/ship.h"
#include <MLV/MLV_all.h>


void load_sprite_ship(Ship* ship, MLV_Image** img);

void draw_ship(Ship* ship, MLV_Image* img);


#endif