#include "../include/ship.h"


/* -------------------- */
void init_ship(Ship* ship)
/* -------------------- */
{
	/* set the northwest corner position for the ship */
	ship->hb.x_NW = WINDOW_WIDTH / 20; /* place the ship in the middle of the screen */
	ship->hb.y_NW = (WINDOW_HEIGHT / 2) - (SHIP_SIZE / 2); /* same */

	/* set the southeast corner position for the ship */
	ship->hb.x_SE = ship->hb.x_NW + SHIP_SIZE;
	ship->hb.y_SE = ship->hb.y_NW + SHIP_SIZE;

	ship->health = 100;
	ship->current_sprite = IDLE;
	ship->speed = 1; /* added to the ship's position to make it move */

	/* set the options, all null when starting */
	ship->has_missile = 0;
	ship->has_double = 0;
	ship->has_laser = 0;
	ship->has_option = 0;
	ship->invulnerability_frames = 0;
	ship->shot_frames_wait = 0;

	/* allocate the list of projectiles */
	ship->projectiles = allocate_shotList();
}

/* -------------------------------------------- */
void move_ship(Ship* ship, int move_x, int move_y)
/* -------------------------------------------- */
{
	/* if the ship will go out of borders */
	if((move_x > 0 && ship->hb.x_SE + ship->speed > WINDOW_WIDTH) || (move_x < 0 && ship->hb.x_NW - ship->speed <= 0))
		return;
	if((move_y > 0 && ship->hb.y_SE + ship->speed > WINDOW_HEIGHT) || (move_y < 0 && ship->hb.y_NW - ship->speed <= 0))
		return;

	/* change the sprite depending on the ship's move on the y axis */
	switch(move_y){
		case 0  : ship->current_sprite = IDLE; 			break;
		case 1  : ship->current_sprite = MOVING_UP; 	break;
		case -1 : ship->current_sprite = MOVING_DOWN; 	break;
		default: break;
	}

	/* move the ship's position (moving the whole hitbox) */
	ship->hb.x_NW += ship->speed * move_x;
	ship->hb.x_SE += ship->speed * move_x;

	ship->hb.y_NW += ship->speed * move_y;
	ship->hb.y_SE += ship->speed * move_y;
}

/* ------------------------------------------------------------------------------------ */
void add_projectile_ship(Ship* ship, int x_proj, int y_proj, int speed, int vect_x, int vect_y)
/* ------------------------------------------------------------------------------------ */
{
	/* if the ship cannot shoot yet */
	if(ship->shot_frames_wait > 0)
		return;

	/* if we reached capacity, arrange the list. */
	if(ship->projectiles.index == ship->projectiles.capacity)
		arrange_list_projectiles(&(ship->projectiles));

	/* if it can shoot, it has to wait to shoot again */
	ship->shot_frames_wait = SHOT_FRAMES_WAIT;

	/* initialize the new projectile to be next to the ship */
	ship->projectiles.list[ship->projectiles.index].hb.x_NW = x_proj;
	ship->projectiles.list[ship->projectiles.index].hb.y_NW = y_proj;
	ship->projectiles.list[ship->projectiles.index].hb.x_SE = x_proj + PROJECTILE_SIZE;
	ship->projectiles.list[ship->projectiles.index].hb.y_SE = y_proj + PROJECTILE_SIZE;
	ship->projectiles.list[ship->projectiles.index].speed = speed;
	ship->projectiles.list[ship->projectiles.index].vect_x = vect_x;
	ship->projectiles.list[ship->projectiles.index].vect_y = vect_y;

	ship->projectiles.active[ship->projectiles.index] = 1;
	ship->projectiles.index++;
}


/* -------------------------------- */
void move_ship_projectiles(Ship* ship)
/* -------------------------------- */
{
	int i;

	for(i = 0 ; i < ship->projectiles.index ; i++){
		/* if the projectile isn't active */
		if(!(ship->projectiles.active[i]))
			continue;

		/* move the projectile's hitbox */
		ship->projectiles.list[i].hb.x_NW += ship->projectiles.list[i].speed * ship->projectiles.list[i].vect_x;
		ship->projectiles.list[i].hb.x_SE += ship->projectiles.list[i].speed * ship->projectiles.list[i].vect_x;
		ship->projectiles.list[i].hb.y_NW += ship->projectiles.list[i].speed * ship->projectiles.list[i].vect_y;
		ship->projectiles.list[i].hb.y_SE += ship->projectiles.list[i].speed * ship->projectiles.list[i].vect_y;

		/* if the projectile goes out of bounds, remove it */
		if(ship->projectiles.list[i].hb.x_NW > WINDOW_WIDTH){
			ship->projectiles.active[i] = 0;
			ship->projectiles.list[i].hb.x_NW = -1;
			ship->projectiles.list[i].hb.y_NW = -1;
		}
	}
}

/* -------------------------------- */
void actualize_frames_ship(Ship* ship)
/* -------------------------------- */
{
	if(ship->invulnerability_frames)
		ship->invulnerability_frames--;

	if(ship->shot_frames_wait)
		ship->shot_frames_wait--;
}