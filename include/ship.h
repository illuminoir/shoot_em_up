#ifndef __SHIP__
#define __SHIP__

#include "../include/projectiles.h"

#define IDLE 0
#define MOVING_UP 1
#define MOVING_DOWN 2
#define SHIP_SIZE WINDOW_WIDTH / 15


typedef struct _ship {
	int x;
	int y;
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

/* TODO */
void add_projectile(Ship* ship, int x_proj, int y_proj);

#endif