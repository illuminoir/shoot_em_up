#include "../include/ship.h"


/* -------------------- */
void init_ship(Ship* ship)
/* -------------------- */
{
	ship->hb.x_NW = WINDOW_WIDTH / 20;
	ship->hb.y_NW = (WINDOW_HEIGHT / 2) - (SHIP_SIZE / 2); /* in the middle of the screen */

	ship->hb.x_SE = ship->hb.x_NW + SHIP_SIZE;
	ship->hb.y_SE = ship->hb.y_NW + SHIP_SIZE;

	ship->health = 100;
	ship->current_sprite = IDLE;
	ship->speed = 1; /* added to the ship's position to make it move */

	ship->has_missile = 0;
	ship->has_double = 0;
	ship->has_laser = 0;
	ship->has_option = 0;
	ship->invulnerability_frames = 0;
	ship->shot_frames_wait = 0;

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


/* --------------------------------------- */
int compare_pos(const void* a, const void* b)
/* --------------------------------------- */
{
	Shot* sa = (Shot *)a;
	Shot* sb = (Shot *)b;

	return sa->x - sb->x;
}

/* --------------------------------------------- */
void arrange_list_projectiles_ship(ShotList* shots)
/* --------------------------------------------- */
{
	int i;

	qsort(shots->list, MAX_CAPACITY, sizeof(Shot), compare_pos);

	for(i = 0 ; shots->list[i].x != -1 ; i++)
		shots->active[i] = 1;
	shots->index = i;

	for(i = shots->index ; i < shots->capacity ; i++)
		shots->active[i] = 0;
}


/* ------------------------------------------------------------------------------------ */
void add_projectile(Ship* ship, int x_proj, int y_proj, int speed, int vect_x, int vect_y)
/* ------------------------------------------------------------------------------------ */
{
	if(ship->shot_frames_wait > 0)
		return;
	if(ship->projectiles.index == ship->projectiles.capacity)
		arrange_list_projectiles_ship(&(ship->projectiles));

	ship->shot_frames_wait = 30;

	ship->projectiles.list[ship->projectiles.index].x = x_proj;
	ship->projectiles.list[ship->projectiles.index].y = y_proj;
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

	/* arrange_projectiles() for when holes */

	for(i = 0 ; i < ship->projectiles.index ; i++){
		if(!(ship->projectiles.active[i]))
			continue;

		ship->projectiles.list[i].x += ship->projectiles.list[i].speed * ship->projectiles.list[i].vect_x;
		ship->projectiles.list[i].y += ship->projectiles.list[i].speed * ship->projectiles.list[i].vect_y;

		/* if the projectile goes out of bounds, remove it */
		if(ship->projectiles.list[i].x > WINDOW_WIDTH){
			ship->projectiles.active[i] = 0;
			ship->projectiles.list[i].x = -1;
			ship->projectiles.list[i].y = -1;
		}
	}
}

/* -------------------------------- */
void actualize_frames_ship(Ship* ship)
/* -------------------------------- */
{
	if(ship->invulnerability_frames > 0)
		ship->invulnerability_frames--;

	if(ship->shot_frames_wait > 0)
		ship->shot_frames_wait--;
}