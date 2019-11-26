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
	ship->invulnerability_frames = 0;

	ship->projectiles = allocate_shotList();
}

/* --------------------------- */
void move_ship(Ship* ship, int move_x, int move_y)
/* --------------------------- */
{
	/* if the ship will go out of borders */
	if((move_x && ship->x + ship->speed >= WINDOW_WIDTH - SHIP_SIZE) || (move_x < 0 && ship->x - ship->speed <= 0))
		return;
	if((move_y && ship->y + ship->speed >= WINDOW_HEIGHT - SHIP_SIZE) || (move_y < 0 && ship->y - ship->speed <= 0))
		return;

	switch(move_y){
		case 0  : ship->current_sprite = IDLE; 			break;
		case 1  : ship->current_sprite = MOVING_UP; 	break;
		case -1 : ship->current_sprite = MOVING_DOWN; 	break;
		default: break;
	}

	ship->x += ship->speed * move_x;
	ship->y += ship->speed * move_y;
}


/* --------------------------- */
void add_projectile(Ship* ship, int x_proj, int y_proj)
/* --------------------------- */
{


	;
}