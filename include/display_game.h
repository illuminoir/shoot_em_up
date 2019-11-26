#ifndef __DISPLAY_GAME__
#define __DISPLAY_GAME__

#include "../include/display_ship.h"
#include "../include/display_enemies.h"
#include <MLV/MLV_all.h>

/* Displays the stars */
void draw_stars(Stars* stars);

/* Displays the entirety of the game using MLV.
 * Parameters : 
 *		Ship* ship 			: pointer to the ship
 *		MLV_Image* img_ship : pointer to the ship's sprite
 *		Stars* stars 		: pointer to the stars structure */
void draw_game(Ship* ship, MLV_Image* img_ship, Stars* stars);

#endif