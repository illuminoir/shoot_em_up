#ifndef __COLLISIONS__
#define __COLLISIONS__

#include "../include/ship.h"
#include "../include/enemy.h"

/* Returns whether the two given hitboxes are colliding or not.
 * Parameters :
 *		Hitbox h1 : the first hitbox
 *		Hitbox h2 : the second hitbox
 * Return : 1 if they collide, 0 otherwise. */
int collision_hitboxes(Hitbox h1, Hitbox h2);

/* Actions for when the ship collides with an enemy projectile :
 * Remove health to the ship, make it invulnerable, delete the projectile.
 * Parameters :
 *		Ship* ship 			  : pointer to the Ship object
 *		ShotList* projectiles : list of the enemy projectiles
 *		int index_proj 		  :	index of the projectile colliding */
void collision_ship_enemy_projectile(Ship* ship, ShotList* projectiles, int index_proj);

/* Actions for when the ship collides with an enemy :
 * Remove health to the ship.
 * Parameters :
 *		Ship* ship 	 : pointer to the Ship object
 *		Enemy* enemy : the enemy colliding */
void collision_ship_enemy(Ship* ship, Enemy* enemy);

/* Actions for when a projecile from the ship collides with an enemy :
 * Delete the projectile, remove the enemy's health and the enemy if it dies.
 * Parameters :
 *		ShotList* projectiles : list of the ship's projectiles
 *		int index_proj 		  :	index of the projectile colliding
 *		Enemy* enemy 		  : the enemy colliding */
void collision_ship_projectile_enemy(ShotList* projectiles, int index_proj, Enemy* enemy);

#endif