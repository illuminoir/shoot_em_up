#ifndef __SHIP__
#define __SHIP__

#include "../include/projectiles.h"

#define IDLE 0
#define MOVING_UP 1
#define MOVING_DOWN 2
#define SHIP_SIZE WINDOW_WIDTH / 15
#define PROJECTILE_SIZE WINDOW_WIDTH / 80
#define SHOT_FRAMES_WAIT 40


typedef struct _ship {
	Hitbox hb;
	int health;
	int current_sprite; /* gives the sprite index depending on the pressed key */
	int speed; /* speed vector */
	int has_missile; /* missle upgrade */
	int has_double; /* double shot upgrade */
	int has_laser; /* laser upgrade */
	int has_option; /* option upgrade */
	int invulnerability_frames; /* when hit become invulnerable for some time */
	int shot_frames_wait; /* when the ship just shot wait a few frames to not overload the screen */
	ShotList projectiles;
}Ship;

/* Initializes the Ship object with base values :
 * Its starting position is in the middle of the screen, the base sprite is idle,
 * speed is set to 1 and the upgrades are not acquired yet.
 * Parameters :
 * 		Ship* ship : pointer on the ship object to initialize */
void init_ship(Ship* ship);

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

#endif