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
	int index_enemy;
	int wait_enemy_spawn;
}Game;

/* Displays the stars
 * Parameters :
 *		Stars* stars 		: pointer to the stars structure */
void draw_stars(Stars* stars);

/* Displays the entirety of the game using MLV.
 * Parameters : 
 *		Game* game 			: pointer to the game state
 *		MLV_Image* img_ship : pointer to the ship's sprite*/
void draw_game(Game* game, MLV_Image* img_ship);

#endif