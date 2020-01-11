#ifndef __GAME__
#define __GAME__

#include "../include/collisions.h"
#include "../include/display_game.h"
#include <time.h>
#include <MLV/MLV_all.h>

#define ENEMY_MAX_CAPACITY 50
#define BONUS_MAX_CAPACITY 15
#define BILLION 1000000000
#define WAIT_ENEMY_SPAWN 600

#define CANNON_SPAWNS 1
#define LONE_SPAWNS 4
#define PATTERNED_SPAWNS 2
#define SPINNING_SPAWNS 3

#define WAIT_MULTIPLE_SPAWNS 30

/* Initializes the game state at the beginning
 * Parameters :
 *		Game* game : pointer to the game object, the state of the game */
void init_game(Game* game);

/* comparison function used when calling qsort in arrange_list_enemies() */
int compare_enemy(const void* a, const void* b);

/* comparison function used when calling qsort in arrange_list_bonuses() */
int compare_bonus(const void* a, const void* b);

/* Arranges the list when "full" i.e. when index equals capacity.
 * arrangement is done so : sort the enemies by their coordinates (all the inactive ones having -1 as coordinates),
 * go through the list until finding an enemy that is inactive, this becomes the new index for the list and
 * all the values from index to the end of the list become free.
 * Parameters :
 * 		Enemy* enemies   : pointer to the list to arrange
 *		int* index_enemy : index to the last active enemy */
void arrange_list_enemies(Enemy* enemies, int* index_enemy);

/* Same principle as arrange_list_enemies() but to sort the bonuses.
 * Parameters :
 * 		Bonus* bonuses   : pointer to the list to arrange
 *		int* index_bonus : index to the last active bonus */
void arrange_list_bonuses(Bonus* bonuses, int* index_bonus);

/* Sets the amount of spawns remaining when generating a new type of enemy.
 * Parameters : 
 *		Game* game : pointer to the game state */
void get_remaining_spawns(Game* game);

/* Generates a new enemy.
 * Parameters :
 *		Game* game : pointer to the game state */
void generate_enemy(Game* game);

/* Generates a new bonus when an enemy dies.
 * Parameters :
 *		Game* game 	 : pointer to the game state
 *		Enemy* enemy : enemy that died */
void generate_bonus(Game *game, Enemy* enemy);

/* Depending on the keys pressed, get the ship event.
 * Possible events are registered from keyboard presses and can be :
 * Move to one of the 4 possible directions, create a new projectile, end the game.
 * Parameters :
 *		Ship* ship 		   : pointer to the ship object
 *		int* x		   	   : the x of the vector if left or right is pressed, 0 if released.
 *		int* y 			   : the y of the vector if up or down is pressed, 0 if released.
 *		int* current_bonus : the current bonus value if the player consumes it */
int get_ship_event(Ship* ship, int* x, int* y, int* current_bonus);

/* Checks for collisions between all the entities :
 * Ship, enemies, projectiles of enemies/the ship.
 * Parameters :
 *		Game* game : pointer to the game state */
void check_all_collisions(Game* game);

/* Move all the entities : the ship, the enemies, their projectiles
 * Parameters :
 *		Game* game : pointer to the game state
 *		int move_x : vector x for the ship's movement
 *		int move_y : vector y for the ship's movement */
void move_all_entities(Game* game, int move_x, int move_y);

/* Actualize the frames for the game objects.
 * In this case, for the ship and enemies, refresh their frames
 * to wait for a new projectile and invulnerability (for the ship).
 * Parameters :
 *		Game* game : pointer to the game state */
void actualize_frames(Game* game);

/* Main loop for the game that runs at 60 frames per second.
 * During this loop everything is resolved : moving the entities, checking for
 * collisions, drawing the game state.
 * Parameters :
 *		Game* game : pointer to the game state */
void main_loop(Game* game);

#endif