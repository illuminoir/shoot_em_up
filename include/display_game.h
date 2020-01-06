#ifndef __DISPLAY_GAME__
#define __DISPLAY_GAME__

#include "../include/display_ship.h"
#include "../include/display_enemies.h"
#include <MLV/MLV_all.h>

/* describes the game state */
typedef struct _game{
	Ship player; /* the player's ship */
	Stars stars; /* the stars for the background */
	Enemy* enemies; /* dynamic list */
	Bonus* bonuses; /* the list of bonuses */
	int index_enemy; /* index of the last active enemy */
	int index_bonus; /* index of the last active bonus */
	int current_enemy; /* type of the last enemy spawn (for the spawning patterns) */
	int remaining_spawns; /* how many spawns of the same enemy are remaining */
	int wait_enemy_spawn; /* time to wait (in frames) between every enemy generation */
	int current_bonus; /* index of the current bonus */
}Game;

/* Displays the stars
 * Parameters :
 *		Stars* stars : pointer to the stars structure */
void draw_stars(Stars* stars);

/* Displays the options 
 * Parameters :
 *		Game* game : the game state */
void draw_options(Game* game);

/* Displays the bonuses
 * Parameters :
 *		Game* game : the game state */
void draw_bonuses(Game* game);

/* Displays the entirety of the game.
 * Parameters : 
 *		Game* game : the game state*/
void draw_game(Game* game);

#endif