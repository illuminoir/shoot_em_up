#include "../include/enemy.h"

/* ----------------------- */
void init_pattern(Pattern* p)
/* ----------------------- */
{
	/* first pattern for the patterned enemy */
	p[0].vect_x = -1;
	p[0].vect_y = 0;
	p[0].frames = 60;

	/* second pattern for the patterned enemy */
	p[1].vect_x = -1;
	p[1].vect_y = -1;
	p[1].frames = 200;

	/* third pattern for the patterned enemy */
	p[2].vect_x = -1;
	p[2].vect_y = 0;
	p[2].frames = 60;

	/* fourth pattern for the patterned enemy */
	p[3].vect_x = -1;
	p[3].vect_y = 1;
	p[3].frames = 200;
}

/* ------------------- */
void init_enemy(Enemy* e)
/* ------------------- */
{
	/* initialize the data common to every type of enemy */
	e->hb.x_NW = WINDOW_WIDTH; 
	e->hb.x_SE = WINDOW_WIDTH;
	e->hb.y_NW = rand() % CANNON_POSITION; 
	e->hb.y_SE = e->hb.y_NW + CANNON_SIZE;
	e->current_sprite = 0;
	e->health = 30;

	switch(e->nature){
		case CANNON : 
			/* if the enemy is a cannon, it starts at a different position and
			 * is the only enemy that has a list of projectiles */
			e->hb.x_NW -= CANNON_SIZE;
			e->hb.y_NW = CANNON_POSITION;
			e->hb.y_SE = CANNON_POSITION + CANNON_SIZE;
			e->vitesse = 0.8;
			e->projectiles = allocate_shotList();
			e->shot_frames_wait = 60;
			e->remaining_shots_angle = 4;
			break;
		case PATTERNED : e->hb.x_NW -= PATTERNED_SIZE; e->vitesse = 0.4; break;
		case LONE_PROJECTILE : e->hb.x_NW -= LONE_PROJECTILE_SIZE; e->vitesse = 2.2; break;
		case SPINNING : e->hb.x_NW -= SPINNING_SIZE; e->vitesse = 2.5; break;
		default: break;
	}

	if(e->nature == PATTERNED){
		e->moves = (Pattern*)malloc(sizeof(Pattern) * 4);
		if(!e->moves)
			; 
		init_pattern(e->moves);
		e->index_pattern = 0;
		e->frames_pattern = e->moves[e->index_pattern].frames;
	}
}
/* ----------------------------- */
void change_pattern_enemy(Enemy *e)
/* ----------------------------- */
{
	/* if we're at the end of a pattern, advance to the next one while cycling through patterns */
	if(!(e->frames_pattern)){
		e->index_pattern = (e->index_pattern  + 1) % 4;
		e->frames_pattern = e->moves[e->index_pattern].frames;
		switch(e->index_pattern){
			case 0 : e->current_sprite = PATTERNED_SPRITE_IDLE; break;
			case 1 : e->current_sprite = PATTERNED_SPRITE_UP; break;
			case 2 : e->current_sprite = PATTERNED_SPRITE_IDLE; break;
			case 3 : e->current_sprite = PATTERNED_SPRITE_DOWN; break;
			default: break;
		}
	}
}
/* ------------------- */
void move_enemy(Enemy *e)
/* ------------------- */
{
	/* if the enemy is patterned, move following along its pattern */
	if(e->nature == PATTERNED){
		change_pattern_enemy(e);
		e->frames_pattern--;
		e->hb.x_NW += (e->vitesse * e->moves[e->index_pattern].vect_x);
		e->hb.x_SE += (e->vitesse * e->moves[e->index_pattern].vect_x);

		e->hb.y_NW += (e->vitesse * e->moves[e->index_pattern].vect_y);
		e->hb.y_SE += (e->vitesse * e->moves[e->index_pattern].vect_y);
	}
	else {
		e->hb.x_NW -= e->vitesse;
		e->hb.x_SE -= e->vitesse;
	}
	/* if the enemy is a lone_projectile, change it's sprite */
	if(e->nature == LONE_PROJECTILE){
		if(!(e->remaining_shots_angle)){
			e->current_sprite = (e->current_sprite + 1) % 2;
			e->remaining_shots_angle = 30;
		}
		else
			e->remaining_shots_angle--;
	}

	/* if the enemy goes beyond the left border, teleport it back to the opposite border */
	if(e->hb.x_SE <= 0){
		e->hb.x_NW = WINDOW_WIDTH - PATTERNED_SIZE;
		e->hb.x_SE = WINDOW_WIDTH;
	}

}

/* ------------------------------------------ */
void move_all_enemies(Enemy* e, int index_enemy)
/* ------------------------------------------ */
{
	int i;

	for(i = 0 ; i < index_enemy ; i++){
		if(e[i].hb.x_NW == -1)
			continue;
		move_enemy(&(e[i]));
	}
}

/* -------------------------------- */
void enemy_add_projectile(Enemy enemy)
/* -------------------------------- */
{

}