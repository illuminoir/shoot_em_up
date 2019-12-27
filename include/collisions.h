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
 * Delete the projectile, decrease the enemy's health and the enemy if it dies.
 * Parameters :
 *		ShotList* projectiles : list of the ship's projectiles
 *		int index_proj 		  :	index of the projectile colliding
 *		Enemy* enemy 		  : the enemy colliding 
 * Return : 1 if an enemy died to generate a bonus, 0 otherwise */
int collision_ship_projectile_enemy(Ship* ship, int index_proj, Enemy* enemy);

/* Actions for when there is collision between the ship and a bonus :
 * Delete the bonus and increase the bonus count by 1.
 * Parameters :
 *		int* current_bonus : the current bonus count
 *		Bonus* bonuses 	   : the list of bonuses
 *		int index_bonus    : the index of the bonus in collision */
void collision_ship_bonus(int* current_bonus, Bonus* bonuses, int index_bonus);

/* Actions for when there is collision between a projectile of the option and an enemy :
 * Delete the projectile and decrease the enemy health and the enemy if it dies.
 * Parameters :
 *		Ship* ship 	   : the ship to get the option
 *		int index_proj : index of the projectile
 *		Enemy* enemy   : the enemy in collision */
int collision_option_projectile_enemy(Ship* ship, int index_proj, Enemy* enemy);

#endif