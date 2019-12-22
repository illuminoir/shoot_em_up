#ifndef __SHIP__
#define __SHIP__

#include "../include/projectiles.h"
#include <MLV/MLV_all.h>

#define IDLE 0
#define MOVING_UP 1
#define MOVING_DOWN 2

#define SPEED_UP 1
#define MISSILE 2
#define DOUBLE 3
#define LASER 4
#define OPTION 5
#define UNKNOWN 6

#define OPTION_SPRITE_1 0
#define OPTION_SPRITE_2 1

/* Option object that shoots along with the ship */
typedef struct _option{
	int x; /* x position for the object */
	int y; /* y position for the object */
	int current_sprite; /* current sprite for the object */
	int frames_to_next_sprite; /* frames until we display the next sprite */
	ShotList projectiles; /* the object's projectiles */
}Option;

typedef struct _ship {
	Hitbox hb; /* ship's hitbox */
	int health; /* ship's health */
	int current_sprite; /* gives the sprite index depending on the pressed key */
	float speed; /* speed vector */
	int has_speed_up; /* speed up upgrade */
	int has_missile; /* missle upgrade */
	int has_double; /* double shot upgrade */
	int has_laser; /* laser upgrade */
	int has_option; /* option upgrade */
	int invulnerability_frames; /* when hit become invulnerable for some time */
	int shot_frames_wait; /* when the ship just shot wait a few frames to not overload the screen */
	ShotList projectiles; /* the ship's projectile */
	Option option; /* option object for when the upgrade is acquired */
}Ship;

/* Initializes the Ship object with base values :
 * Its starting position is in the middle of the screen, the base sprite is idle,
 * speed is set to 1 and the upgrades are not acquired yet.
 * Parameters :
 * 		Ship* ship : pointer on the ship object to initialize */
void init_ship(Ship* ship);

/* Change the y axis for the ship and its sprite depending on its move_y vector.
 * Parameters : 
 * 		Ship* ship : pointer on the ship
 *		int move_y : the y vector to move the ship */
void change_ship_y_axis(Ship* ship, int move_y);

/* Moves the ship.
 * Adds move_x or move_y times the ship's speed to it's x or y coordinate respectively.
 * Parameters :
 * 		Ship* ship : pointer on the ship object to initialize
 *		int move_x : vector to move the x coordinate (can be -1, 0 or 1) 
 *		int move_y : vector to move the y coordinate (can be -1, 0 or 1) */
void move_ship(Ship* ship, int move_x, int move_y);

/* Add a new projectile to the ship's list of projectiles
 * Parameters :
 *		Ship* ship : pointer on the ship object
 *		int x_proj : x position for the projectile
 *		int y_proj : y position for the projectile
 *		int speed  : speed for the projectile
 *		int vect_x : x vector for the direction in which the projectiles goes
 * 		int vect_y : y vector for the direction in which the projectiles goes */
void add_projectile_ship(Ship* ship, int x_proj, int y_proj, int speed, int vect_x, int vect_y);

/* Move all the of the ship's projectiles 
 * Parameters :
 *		Ship* ship : pointer on the ship object, to move its projectiles */
void move_ship_projectiles(Ship* ship);

/* Actualizes the frames for invulnerability and waiting between shots
 * Parameters :
 * 		Ship* ship : pointer to the ship object */
void actualize_frames_ship(Ship* ship);

/* Consume the bonus and add the upgrade depending on how much was consumed.
 * Parameters :
 *		int* current_bonus : the current bonus that will be reset after consumption.
 *		Ship* ship 		   : pointer on the ship */
void consume_bonus(int* current_bonus, Ship* ship);

#endif