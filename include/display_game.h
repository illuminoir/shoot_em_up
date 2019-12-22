#ifndef __DISPLAY_GAME__
#define __DISPLAY_GAME__

#include "../include/display_ship.h"
#include "../include/display_enemies.h"
#include <MLV/MLV_all.h>

/* describes the game state */
typedef struct _game{
	Ship player;
	Stars stars;
	Enemy* enemies; /* dynamic list */
	Bonus* bonuses;
	int index_enemy;
	int index_bonus;
	int wait_enemy_spawn;
	int current_bonus;
}Game;

/* Displays the stars
 * Parameters :
 *		Stars* stars 		: pointer to the stars structure */
void draw_stars(Stars* stars);

void draw_options(Game* game);

void draw_bonuses(Game* game);

/* Displays the entirety of the game using MLV.
 * Parameters : 
 *		Game* game 			: pointer to the game state*/
void draw_game(Game* game);

#endif