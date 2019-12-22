#ifndef __DISPLAY_ENEMIES__
#define __DISPLAY_ENEMIES__

#include "../include/enemy.h"
#include <MLV/MLV_all.h>

/* Draw the enemies on the screen using the MLV functions.
 * Parameters :
 * 		Enemy* enemies : the list of enemies
 *		int index	   : index of the last enemy */
void draw_enemies(Enemy* enemies, int index);


#endif