#ifndef __DISPLAY_ENEMIES__
#define __DISPLAY_ENEMIES__

#include "../include/enemy.h"
#include <MLV/MLV_all.h>

/* Load the sprite for a patterned enemy.
 * Parameters :
 *		MLV_Image** sprite : pointer to the image to get the sprite
 *		int current_sprite : value of the enemy's current sprite */
void get_sprite_patterned(MLV_Image** sprite, int current_sprite);

/* Load the sprite for a lone projectile enemy.
 * Parameters :
 *		MLV_Image** sprite : pointer to the image to get the sprite
 *		int current_sprite : value of the enemy's current sprite */
void get_sprite_lone_projectile(MLV_Image** sprite, int current_sprite);

/* Load the sprite for a cannon enemy.
 * Parameters :
 *		MLV_Image** sprite : pointer to the image to get the sprite
 *		int current_sprite : value of the enemy's current sprite */
void get_sprite_cannon(MLV_Image** sprite, int current_sprite);

/* Load the sprite for a spinning enemy.
 * Parameters :
 *		MLV_Image** sprite : pointer to the image to get the sprite
 *		int current_sprite : value of the enemy's current sprite */
void get_sprite_spinning(MLV_Image** sprite, int current_sprite);

/* Draw the enemies on the screen using the MLV functions.
 * Parameters :
 * 		Enemy* enemies : the list of enemies
 *		int index	   : index of the last enemy */
void draw_enemies(Enemy* enemies, int index);


#endif