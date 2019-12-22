#ifndef __DISPLAY_SHIP__
#define __DISPLAY_SHIP__

#include "../include/ship.h"
#include <MLV/MLV_all.h>

/* Draws the ship's projectiles 
 * Depending on whether laser upgrade is obtained or not, two different
 * sprites exist.
 * Parameters :
 *		Ship* ship : pointer to the ship to draw its projectiles */
void draw_projectiles_ship(Ship* ship);

/* Function that draws the ship at its coordinates. 
 * Parameters :
 *		Ship* ship 		: pointer to the ship to get its coordinates.*/
void draw_ship(Ship* ship);


#endif