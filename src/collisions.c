#include "../include/collisions.h"

/* -------------------------------------- */
int collision_hitboxes(Hitbox h1, Hitbox h2)
/* -------------------------------------- */
{
	if(((h1.x_NW <= h2.x_NW) && (h1.x_SE >= h2.x_SE)) 
		&& ((h1.y_NW <= h2.y_NW) && (h1.y_SE >= h2.y_SE)))
		return 1;

	if(((h2.x_NW <= h1.x_NW) && (h2.x_SE >= h1.x_SE)) 
		&& ((h2.y_NW <= h1.y_NW) && (h2.y_SE >= h1.y_SE)))
		return 1;

	return 0;
}

/* --------------------------------------------------------------------------------- */
void collision_ship_enemy_projectile(Ship* ship, ShotList* projectiles, int index_proj)
/* --------------------------------------------------------------------------------- */
{
	/* the ship is hit, loses health and is invulnerable for some time */
	ship->health -= 10;
	ship->invulnerability_frames = 120;

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

/* ----------------------------------------------------------------------- */
int collision_ship_projectile_enemy(Ship* ship, int index_proj, Enemy* enemy)
/* ----------------------------------------------------------------------- */
{
	/* ship projectile hit an enemy, remove it */
	ship->projectiles.list[index_proj].hb.x_NW = -1;
	ship->projectiles.list[index_proj].hb.y_NW = -1;
	ship->projectiles.active[index_proj] = 0;

	/* enemy loses health */
	if(ship->has_laser)
		enemy->health -= 10;
	enemy->health -= 10;

	/* if the enemy dies, try to generate a bonus then remove it */
	if(enemy->health < 0)
		return 1;

	return 0;
}

/* ------------------------------------------------------------------------ */
void collision_ship_bonus(int* current_bonus, Bonus* bonuses, int index_bonus)
/* ------------------------------------------------------------------------ */
{
	/* if max bonus isn't reached */
	if(*current_bonus < 5)
		*current_bonus += 1;

	/* disable the bonus */
	bonuses[index_bonus].hb.x_NW = -1;
	bonuses[index_bonus].hb.y_NW = -1; 
}

/* ------------------------------------------------------------------------- */
int collision_option_projectile_enemy(Ship* ship, int index_proj, Enemy* enemy)
/* ------------------------------------------------------------------------- */
{
	/* option's projectile hit an enemy, remove it */
	ship->option.projectiles.list[index_proj].hb.x_NW = -1;
	ship->option.projectiles.list[index_proj].hb.y_NW = -1;
	ship->option.projectiles.active[index_proj] = 0;

	/* enemy loses health */
	if(ship->has_laser)
		enemy->health -= 10;
	enemy->health -= 10;

	/* if the enemy dies, try to generate a bonus then remove it */
	if(enemy->health < 0)
		return 1;

	return 0;
}