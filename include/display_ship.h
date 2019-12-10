#ifndef __DISPLAY_SHIP__
#define __DISPLAY_SHIP__

#include "../include/ship.h"
#include <MLV/MLV_all.h>

/* Loads the correct sprite for the ship.
 * The correct sprite depends on the ship's movement on the y axis :
 * Going down, going up or staying idle (x axis can still move).
 * Parameters :
 *		Ship* ship 		: pointer to the ship to get its sprite.
 * 		MLV_Image** img : pointer to where the sprite will be stored. */
void load_sprite_ship(Ship* ship, MLV_Image** img);

/* Draws the ship's projectiles 
 * Depending on whether laser upgrade is obtained or not, two different
 * sprites exist.
 * Parameters :
 *		Ship* ship : pointer to the ship to draw its projectiles */
void draw_projectiles_ship(Ship* ship);

/* Function that draws the ship at its coordinates. 
 * Parameters :
 *		Ship* ship 		: pointer to the ship to get its coordinates.
 * 		MLV_Image* img  : pointer to the image to draw for the ship. */
void draw_ship(Ship* ship, MLV_Image* img);


#endif