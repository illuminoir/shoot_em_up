#ifndef __SHIP__
#define __SHIP__

#include "../include/projectiles.h"

#define IDLE 0
#define MOVING_UP 1
#define MOVING_DOWN 2
/* #define SPRITE_SIZE ?? */

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

void init_ship(Ship* ship);

void move_ship(Ship* ship, int move_x, int move_y);

void add_projectile(Ship* ship, int x_proj, int y_proj);

#endif