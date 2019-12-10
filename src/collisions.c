#include "../include/collisions.h"

/* -------------------------------------- */
int collision_hitboxes(Hitbox h1, Hitbox h2)
/* -------------------------------------- */
{
	if((h1.x_NW < h2.x_SE && h1.x_SE > h2.x_NW) 
		&& (h1.y_NW < h2.y_SE && h1.y_SE > h2.y_NW))
		return 1;
	else if((h1.x_NW < h2.x_NW && h1.x_SE > h2.x_SE)
		&& (h1.y_NW < h2.y_NW && h1.y_SE > h2.y_SE))
		return 1;
	return 0;
}

/* --------------------------------------------------------------------------------- */
void collision_ship_enemy_projectile(Ship* ship, ShotList* projectiles, int index_proj)
/* --------------------------------------------------------------------------------- */
{
	/* the ship is hit, loses health and is invulnerable for some time */
	ship->health -= 10;
	ship->invulnerability_frames = 60;

	/* enemy projectile hit the ship, remove it */
	projectiles->list[index_proj].hb.x_NW = -1;
	projectiles->list[index_proj].hb.y_NW = -1;
	projectiles->active[index_proj] = 0;
}

/* --------------------------------------------- */
void collision_ship_enemy(Ship* ship, Enemy* enemy)
/* --------------------------------------------- */
{
	/* the ship is hit, loses health and is invulnerable for some time */
	ship->health -= 10;
	ship->invulnerability_frames = 120;	
}

/* ----------------------------------------------------------------------------------- */
void collision_ship_projectile_enemy(ShotList* projectiles, int index_proj, Enemy* enemy)
/* ----------------------------------------------------------------------------------- */
{
	int i;

	for(i = 0 ; i < projectiles->capacity ; i++){
		printf("(%d)", projectiles->active[i]);
	}

	/* ship projectile hit an enemy, remove it */
	projectiles->list[index_proj].hb.x_NW = -1;
	projectiles->list[index_proj].hb.y_NW = -1;
	projectiles->active[index_proj] = 0;

	/* enemy loses health */
	enemy->health -= 10;

	/* if the enemy dies, remove it */
	if(!(enemy->health)){
		printf("\nMORT\n");
		enemy->hb.x_NW = -1;
		enemy->hb.y_NW = -1;
	}

	printf("\n");

	for(i = 0 ; i < projectiles->capacity ; i++){
		printf("(%d)", projectiles->active[i]);
	}

	printf("\n\n");
}