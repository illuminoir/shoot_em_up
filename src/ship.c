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

	ship->health = 100000;
	ship->current_sprite = IDLE;
	ship->speed = 0.5; /* added to the ship's position to make it move */

	/* set the options, all null when starting */
	ship->has_speed_up = 0;
	ship->has_missile = 0;
	ship->has_double = 0;
	ship->has_laser = 0;
	ship->has_option = 0;
	ship->invulnerability_frames = 0;
	ship->shot_frames_wait = 0;

	/* allocate the list of projectiles */
	ship->projectiles = allocate_shotList();

	/* set the option to disabled */
	ship->option.x = -1;
	ship->option.y = -1;
	ship->option.current_sprite = OPTION_SPRITE_1;
	ship->option.frames_to_next_sprite = 30;
	ship->option.projectiles = allocate_shotList();
}

/* ----------------------------------------- */
void change_ship_y_axis(Ship* ship, int move_y)
/* ----------------------------------------- */
{
	/* if has option upgrade, give it a default Y position */
	if(ship->has_option)
		ship->option.y = ship->hb.y_SE + (SHIP_SIZE / 2);

	/* get the sprite depending on the ship's y move and move the option accordingly */
	switch(move_y){
		case 0  :
			ship->current_sprite = IDLE;
			break;
		case 1  : 
			ship->current_sprite = MOVING_UP;
		 	if(ship->has_option) 
		 		ship->option.y = ship->hb.y_NW - (SHIP_SIZE / 2);
		 	break;
		case -1 : 
			ship->current_sprite = MOVING_DOWN;
		 	if(ship->has_option) 
		 		ship->option.y = ship->hb.y_SE + (SHIP_SIZE / 2);
		 	break;
		default: break;
	}
}

/* -------------------------------------------- */
void move_ship(Ship* ship, int move_x, int move_y)
/* -------------------------------------------- */
{
	float speed;

	/* apply the speed up upgrade if acquired */
	if(ship->has_speed_up)
		speed = ship->speed * 2.5;
	else
		speed = ship->speed;


	/* if the ship will go out of borders */
	if((move_x > 0 && ship->hb.x_SE + ship->speed > WINDOW_WIDTH) || (move_x < 0 && ship->hb.x_NW - ship->speed <= 0))
		return;
	if((move_y > 0 && ship->hb.y_SE + ship->speed > WINDOW_HEIGHT) || (move_y < 0 && ship->hb.y_NW - ship->speed <= 0))
		return;

	/* change the sprite depending on the ship's move on the y axis */
	change_ship_y_axis(ship, move_y);

	/* move the ship's position (moving the whole hitbox) */
	ship->hb.x_NW += speed * move_x;
	ship->hb.x_SE += speed * move_x;

	ship->hb.y_NW += speed * move_y;
	ship->hb.y_SE += speed * move_y;

	/* if the ship has the option, move it as well */
	if(ship->has_option){
		/* if it's time to go to the next sprite */
		if(!(ship->option.frames_to_next_sprite)){
			ship->option.current_sprite = (ship->option.current_sprite + 1 ) % 2;
			ship->option.frames_to_next_sprite = 30;
		}
		else
			ship->option.frames_to_next_sprite--;
		/* move the option with the ship */
		ship->option.x = ship->hb.x_NW - (SHIP_SIZE / 2);
	}
}

/* ----------------------------------------------------------------------------------------- */
void add_projectile_ship(Ship* ship, int x_proj, int y_proj, int speed, int vect_x, int vect_y)
/* ----------------------------------------------------------------------------------------- */
{
	/* if the ship cannot shoot yet */
	if(ship->shot_frames_wait > 0)
		return;

	/* add the projectile */
	add_projectile(&(ship->projectiles), x_proj, y_proj,x_proj + PROJECTILE_SIZE, y_proj + PROJECTILE_SIZE, 
		speed, vect_x, vect_y);

	/* if it can shoot, it has to wait to shoot again */
	ship->shot_frames_wait = SHOT_FRAMES_WAIT;

	/* if ship has double shot upgrade, same process of adding a projectile but lower in y */
	if(ship->has_double){

		/* move the first projectile a little higher */
		ship->projectiles.list[ship->projectiles.index - 1].hb.y_NW -= SHIP_SIZE / 5;
		ship->projectiles.list[ship->projectiles.index - 1].hb.y_SE -= SHIP_SIZE / 5;

		/* add the second projectile */
		add_projectile(&(ship->projectiles), x_proj, y_proj + (SHIP_SIZE / 8),x_proj + PROJECTILE_SIZE,
			y_proj + (SHIP_SIZE / 8) + PROJECTILE_SIZE, speed, vect_x, vect_y);
	}

	/* if the ship has the option upgrade */
	if(ship->has_option && ship->option.x != -1){
		add_projectile(&(ship->projectiles), ship->option.x + 5 + SHIP_OPT_SIZE, ship->option.y + (SHIP_OPT_SIZE / 2) - 5,
			ship->option.x + 5 + SHIP_OPT_SIZE + PROJECTILE_SIZE, ship->option.y + (SHIP_OPT_SIZE * 3 / 2) + PROJECTILE_SIZE - 5,
			speed, vect_x, vect_y);
	}

	/* play the shooting sound */
	MLV_play_sound(ship_shoot_sound, 1.0);
}


/* -------------------------------- */
void move_ship_projectiles(Ship* ship)
/* -------------------------------- */
{
	move_projectiles(&(ship->projectiles));

	if(ship->has_option)
		move_projectiles(&(ship->option.projectiles));
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


/* ------------------------------------------- */
void consume_bonus(int* current_bonus, Ship* ship)
/* ------------------------------------------- */
{
	switch(*current_bonus){
		case SPEED_UP : ship->has_speed_up = 1; break;
		case MISSILE : ship->has_missile = 1; break;
		case DOUBLE : ship->has_double = 1; break;
		case LASER : ship->has_laser = 1; break;
		case OPTION : ship->has_option = 1; break;
		case UNKNOWN : break; /* spawn a big bomb ? a boss ? */
		default: break;
	}

	/* reset the bonus count */
	*current_bonus = 0;
}