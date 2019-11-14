#include "../include/ship.h"


/* --------------------------- */
void init_ship(Ship* ship)
/* --------------------------- */
{
	ship->x = WINDOW_WIDTH / 20;
	ship->y = (WINDOW_HEIGHT / 2) /*- (SPRITE_SIZE / 2)*/; /* in the middle of the screen */

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

/* --------------------------- */
void move_ship(Ship* ship, int move_x, int move_y)
/* --------------------------- */
{
	if((move_x && ship->x == WINDOW_WIDTH) || (move_x < 0 && ship->x == 0))
		return;
	if((move_y && ship->y == WINDOW_HEIGHT) || (move_y < 0 && ship->y == 0))
		return;

	ship->x += ship->speed * move_x;
	ship->y += ship->speed * move_y;
}
