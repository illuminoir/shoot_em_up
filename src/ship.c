#include "../include/ship.h"


/* --------------------------- */
void init_ship(Ship* ship)
/* --------------------------- */
{
	ship->x = WINDOW_SIZE_X / 20;
	ship->y = (WINDOW_SIZE_Y / 2) /*- (SPRITE_SIZE / 2)*/; /* in the middle of the screen */

	ship->health = 100;
	ship->current_sprite = IDLE;
	ship->speed = 1; /* added to the ship's position to make it move */

	ship->has_missile = 0;
	ship->has_double = 0;
	ship->has_laser = 0;
	ship->has_option = 0;
/*
	projectiles = (Tir *)malloc(sizeof(Tir) * 100);
*/
}
