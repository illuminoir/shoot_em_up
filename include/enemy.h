#ifndef __ENEMY__
#define __ENEMY__

#include "../include/projectiles.h"
#include <math.h>

#define CANNON 0
#define LONE_PROJECTILE 1
#define PATTERNED 2
#define SPINNING 3

#define CANNON_IDLE 0
#define CANNON_ANGLE_1 1
#define CANNON_ANGLE_2 2

#define LONE_PROJECTILE_SPRITE_1 0
#define LONE_PROJECTILE_SPRITE_2 1

#define PATTERNED_SPRITE_IDLE 0 
#define PATTERNED_SPRITE_UP 1
#define PATTERNED_SPRITE_DOWN 2

#define SPINNING_SPRITE_1 0
#define SPINNING_SPRITE_2 1
#define SPINNING_SPRITE_3 2
#define SPINNING_SPRITE_4 3

#define CANNON_SIZE 60
#define LONE_PROJECTILE_SIZE 60
#define PATTERNED_SIZE 80
#define SPINNING_SIZE 60

#define CANNON_POSITION WINDOW_HEIGHT - CANNON_SIZE

typedef struct _Pattern{
	int vect_x;
	int vect_y;
	int frames;
}Pattern;

typedef struct _enemy{
	Hitbox hb;
	int health; /* enemy's health */
	int nature; /* the type of enemy that gives the pattern */
	float vitesse; /* depends on nature as well */
	Pattern* moves; /* amount of patterns depends on nature */
	int current_sprite; /* the current sprite for display */
	ShotList projectiles; /* possibly null depending on nature */
	int shot_frames_wait; /* when the enemy just shot wait a few frames to not overload the screen */
	int remaining_shots_angle;
	int frames_pattern;
	int index_pattern;
}Enemy;

/* Initializes the patterns for the patterned enemy.
 * Parameters :
 * 		Pattern* p : list of the patterns */
void init_pattern(Pattern* p);

/* Initializes an enemy depending on its nature.
 * Parameters :
 *		Enemy* e : the enemy to initialize */
void init_enemy(Enemy* e);

/* Move an enemy. 
 * Parameters :
 *		Enemy* enemy : the enemy to move */
void move_enemy(Enemy *enemy);

/* Move all the enemies active on the game
 * Parameters :
 *		Enemy* e 		: the list of enemies to move
 *		int index_enemy : index of the last enemy */
void move_all_enemies(Enemy* e, int index_enemy);

/* Add a projectile to the enemy's list, if it's a cannon. */
void enemy_add_projectile(Enemy enemy);

#endif