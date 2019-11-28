#ifndef __GAME__
#define __GAME__

#include "../include/collisions.h"
#include "../include/display_game.h"
#include <time.h>
#include <MLV/MLV_all.h>


#define BILLION 1000000000

/* Depending on the keys pressed, get the ship event.
 * Possible events are registered from keyboard presses and can be :
 * Move to one of the 4 possible directions, create a new projectile, end the game.
 * Parameters :
 *		Ship* ship 				: pointer to the ship object
 *		int* x					: the x of the vector if left or right is pressed, 0 if released.
 *		int* y 					: the y of the vector if up or down is pressed, 0 if released. */
int get_ship_event(Ship* ship, int* x, int* y);


/* missing enemies */
void main_loop(Ship* ship, Stars* stars);

#endif