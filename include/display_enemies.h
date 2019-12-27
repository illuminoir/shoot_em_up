#ifndef __DISPLAY_ENEMIES__
#define __DISPLAY_ENEMIES__

#include "../include/enemy.h"
#include <MLV/MLV_all.h>

/* Draws the projectiles for an enemy.
 * Parameters :
 *		ShotList* projectiles : the list of projectiles */
void draw_enemy_projectiles(ShotList* projectiles);

/* Draw the enemies on the screen using the MLV functions.
 * Parameters :
 * 		Enemy* enemies : the list of enemies
 *		int index	   : index of the last enemy */
void draw_enemies(Enemy* enemies, int index);


#endif