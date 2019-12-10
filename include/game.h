#ifndef __GAME__
#define __GAME__

#include "../include/collisions.h"
#include "../include/display_game.h"
#include <time.h>
#include <MLV/MLV_all.h>

#define ENEMY_MAX_CAPACITY 30
#define BILLION 1000000000
#define WAIT_ENEMY_SPAWN 500

/* Initializes the game state at the beginning
 * Parameters :
 *		Game* game : pointer to the game object, the state of the game */
void init_game(Game* game);

/* comparison function used when calling qsort in arrange_list_enemies() */
int compare_enemy(const void* a, const void* b);

/* Arranges the list when "full" i.e. when index equals capacity.
 * arrangement is done so : sort the enemies by their coordinates (all the inactive ones having -1 as coordinates),
 * go through the list until finding an enemy that is inactive, this becomes the new index for the list and
 * all the values from index to the end of the list become free.
 * Parameters :
 * 		Enemy* enemies   : pointer to the list to arrange
 *		int* index_enemy : index to the last active enemy */
void arrange_list_enemies(Enemy* enemies, int* index_enemy);

/* Generates a new enemy.
 * Parameters :
 *		Game* game : pointer to the game state */
void generate_enemy(Game* game);

/* Depending on the keys pressed, get the ship event.
 * Possible events are registered from keyboard presses and can be :
 * Move to one of the 4 possible directions, create a new projectile, end the game.
 * Parameters :
 *		Ship* ship 				: pointer to the ship object
 *		int* x					: the x of the vector if left or right is pressed, 0 if released.
 *		int* y 					: the y of the vector if up or down is pressed, 0 if released. */
int get_ship_event(Ship* ship, int* x, int* y);

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

/* Main loop for the game that runs at 60 frames per second.
 * During this loop everything is resolved : moving the entities, checking for
 * collisions, drawing the game state.
 * Parameters :
 *		Game* game : pointer to the game state */
void main_loop(Game* game);

#endif