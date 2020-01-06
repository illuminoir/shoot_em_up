#ifndef __ENEMY__
#define __ENEMY__

#include "../include/projectiles.h"
#include <math.h>

#define PI 3.14159265358979323846

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

#define BONUS_FIRST_SPRITE 0
#define BONUS_SECOND_SPRITE 1

#define SHOTS_FOR_ANGLE 4
#define FRAMES_WAIT_BETWEEN_ANGLES 480
#define FRAMES_WAIT_BETWEEN_SHOTS 120

#define LONE_PROJECTILE_SPRITES 2
#define SPINNING_SPRITES 4

#define CANNON_POSITION WINDOW_HEIGHT - CANNON_SIZE
#define ENEMY_POSITION WINDOW_HEIGHT / 20

typedef struct _Pattern{
	int vect_x;
	int vect_y;
	int frames;
}Pattern;

typedef struct _enemy{
	Hitbox hb; /* enemy's hitbox */
	int health; /* enemy's health */
	int nature; /* the type of enemy that gives the pattern */
	float speed; /* depends on nature as well */
	Pattern* moves; /* amount of patterns depends on nature */
	int current_sprite; /* the current sprite for display */
	ShotList projectiles; /* possibly null depending on nature */
	int shot_frames_wait; /* when the enemy just shot wait a few frames to not overload the screen */
	int remaining_shots_angle; /* for cannon enemies a count of shots to do for each angle */
	int remaining_frames_sprite; /* the remaining frames for this current sprite */
	int frames_pattern; /* frames for a pattern */
	int index_pattern; /* index of the current pattern */
	int drop_rate; /* is a percentage, a value of 3 meaning a 3% drop rate */
}Enemy;

typedef struct _bonus {
	Hitbox hb;
	float speed;
	int current_sprite;
	int frames_to_next_sprite;
}Bonus;

/* Initializes a bonus.
 * Parameters :
 *		Bonus* b : the bonus to initialize
 *		int x 	 : x coordinate of the enemy that died and generated this bonus
 *		int y 	 : y coordinate of the enemy that died and generated this bonus */
void init_bonus(Bonus* b, int x, int y);

/* Initializes the patterns for the patterned enemy.
 * Parameters :
 * 		Pattern* p : list of the patterns */
void init_pattern(Pattern* p);

/* Initializes an enemy depending on its nature.
 * Parameters :
 *		Enemy* e : the enemy to initialize */
void init_enemy(Enemy* e);

/* Changes the pattern for patterned enemies.
 * Parameters :
 *		Enemy* e : the enemy to modify. */
void change_pattern_enemy(Enemy *e);

/* Move an enemy. 
 * Parameters :
 *		Enemy* enemy : the enemy to move */
void move_enemy(Enemy *enemy);

/* Moves a bonus
 * Parameters :
 *		Bonus* b : the bonus to move */
void move_bonus(Bonus* b);

/* Move all the enemies active on the game
 * Parameters :
 *		Enemy* e 		: the list of enemies to move
 *		int index_enemy : index of the last enemy */
void move_all_enemies(Enemy* e, int index_enemy);

/* Move all the bonuses active on the game
 * Parameters :
 *		Bonus *b 		 : the list of bonuses
 *		int index_bonuss : index of the last bonus */
void move_all_bonuses(Bonus* b, int index_bonus);

/* Actualize the frames for an enemy : the frames between shots or
 * until the next sprite.
 * Parameters :
 *		Enemy* enemy : the enemy. */		
void actualize_frames_enemy(Enemy* enemy);

/* Add a projectile to the enemy's list, if it's a cannon.
 * Parameters :
 *		Enemy* enemy : the enemy to add a projectile to. */
void enemy_add_projectile(Enemy* enemy);

/* Move all the enemy projectiles.
 * Parameters :
 *		Enemy* enemies  : the list of enemies.
 *		int index_enemy : the index of the last enemy. */
void move_all_enemies_projectiles(Enemy* enemies, int index_enemy);

/* Add projectile to all the enemies, if possible.
 * Parameters :
 *		Enemy* enemies  : the list of enemies
 *		int index_enemy : index of the last enemy */
void add_projectiles_to_enemies(Enemy* enemies, int index_enemy);

#endif