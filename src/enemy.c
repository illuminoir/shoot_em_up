#include "../include/enemy.h"

/* global variable to make the sinusoidal movement */
float ticks;

/* --------------------------------- */
void init_bonus(Bonus* b, int x, int y)
/* --------------------------------- */
{
	b->hb.x_NW = x;
	b->hb.y_NW = y;
	b->hb.x_SE = x + BONUS_SIZE;
	b->hb.y_SE = y + BONUS_SIZE;

	b->speed = 2;

	b->current_sprite = 0;
	b->frames_to_next_sprite = 30;
}

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
	e->hb.y_NW = rand() % (CANNON_POSITION - ENEMY_POSITION) + ENEMY_POSITION; 
	e->hb.y_SE = e->hb.y_NW + CANNON_SIZE;
	e->current_sprite = 0;
	e->health = 30;
	e->drop_rate = 5;

	switch(e->nature){
		case CANNON : 
			/* if the enemy is a cannon, it starts at a different position and
			 * is the only enemy that has a list of projectiles */
			e->hb.x_NW -= CANNON_SIZE;
			e->hb.y_NW = CANNON_POSITION;
			e->hb.y_SE = CANNON_POSITION + CANNON_SIZE;
			e->speed = 0.4;
			e->projectiles = allocate_shotList();
			e->shot_frames_wait = 0;
			e->remaining_shots_angle = 4;
			break;
		case PATTERNED : e->hb.x_NW -= PATTERNED_SIZE; e->speed = 0.4; break;
		case LONE_PROJECTILE : e->hb.x_NW -= LONE_PROJECTILE_SIZE; e->speed = 2.2; e->drop_rate = 20; break;
		case SPINNING : e->hb.x_NW -= SPINNING_SIZE; e->speed = 2; break;
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
		e->hb.x_NW += (e->speed * e->moves[e->index_pattern].vect_x);
		e->hb.x_SE += (e->speed * e->moves[e->index_pattern].vect_x);

		e->hb.y_NW += (e->speed * e->moves[e->index_pattern].vect_y);
		e->hb.y_SE += (e->speed * e->moves[e->index_pattern].vect_y);
	}
	/* if the enemy is spinning, make it move along a sinusoidal */
	else if(e->nature == SPINNING){
		e->hb.x_NW -= e->speed;
		e->hb.x_SE -= e->speed;

		e->hb.y_NW += sin(ticks * (PI / 180));
		e->hb.y_SE += sin(ticks * (PI / 180));
	}

	/* otherwise, it moves following a straight line */
	else {
		e->hb.x_NW -= e->speed;
		e->hb.x_SE -= e->speed;
	}
	/* if the enemy is a lone_projectile or spinning, change its sprite */
	if(!(e->remaining_frames_sprite)){
		e->remaining_frames_sprite = 30;
		if(e->nature == LONE_PROJECTILE)
			e->current_sprite = (e->current_sprite + 1) % LONE_PROJECTILE_SPRITES;
		else if(e->nature == SPINNING)
			e->current_sprite = (e->current_sprite + 1) % SPINNING_SPRITES;
	}
	else
		e->remaining_frames_sprite--;

	/* if the enemy goes beyond the left border, teleport it back to the opposite border */
	if(e->hb.x_SE <= 0){
		e->hb.x_NW = WINDOW_WIDTH - PATTERNED_SIZE;
		e->hb.x_SE = WINDOW_WIDTH;
	}
}

/* ------------------- */
void move_bonus(Bonus* b)
/* ------------------- */
{
		b->hb.x_NW -= b->speed;
		b->hb.x_SE -= b->speed;

		/* if the bonus goes past the left border, remove it */
		if(b->hb.x_NW < 0){
			b->hb.x_NW = -1;
			b->hb.y_NW = -1;
		}

		/* get the next sprite */
		if(!(b->frames_to_next_sprite)){
			b->current_sprite = (b->current_sprite + 1) % 2;
			b->frames_to_next_sprite = 30;
		}
		else
			b->frames_to_next_sprite--;
}

/* ------------------------------------------ */
void move_all_enemies(Enemy* e, int index_enemy)
/* ------------------------------------------ */
{
	int i;

	for(i = 0 ; i < index_enemy ; i++){
		/* if the enemy isn't active */
		if(e[i].hb.x_NW == -1)
			continue;
		move_enemy(&(e[i]));
	}
	
	ticks+= 0.5;
}

/* ------------------------------------------ */
void move_all_bonuses(Bonus* b, int index_bonus)
/* ------------------------------------------ */
{
	int i;

	for(i = 0 ; i < index_bonus ; i++){
		/* if the bonus isn't active */
		if(b[i].hb.x_NW == -1)
			continue;
		move_bonus(&(b[i]));
	}
}

/* ----------------------------------- */
void actualize_frames_enemy(Enemy* enemy)
/* ----------------------------------- */
{
	if(enemy->shot_frames_wait)
		enemy->shot_frames_wait--;
}

/* --------------------------------- */
void enemy_add_projectile(Enemy* enemy)
/* --------------------------------- */
{
	/* if the enemy cannot shoot yet */
	if(enemy->shot_frames_wait)
		return;

	/* the next shot will be after this many frames */
	enemy->shot_frames_wait = FRAMES_WAIT_BETWEEN_SHOTS;

	/* add a projectile on the right angle depending on the sprite */
	if(enemy->current_sprite == CANNON_ANGLE_1)
		add_projectile(&(enemy->projectiles), enemy->hb.x_NW - 5 - PROJECTILE_SIZE, enemy->hb.y_NW - 5 - PROJECTILE_SIZE,
			enemy->hb.x_NW - 5, enemy->hb.y_NW - 5, 0.3, -3, -2);

	if(enemy->current_sprite == CANNON_ANGLE_2)
		add_projectile(&(enemy->projectiles), enemy->hb.x_NW + 20 - PROJECTILE_SIZE, enemy->hb.y_NW - 5 - PROJECTILE_SIZE,
			enemy->hb.x_NW - 5, enemy->hb.y_NW - 5, 0.2, -2.8, -3);

	enemy->remaining_shots_angle--;

	/* if the enemy has done all the shots for a given angle, advance to the next one */
	if(!(enemy->remaining_shots_angle)){
		enemy->current_sprite = (enemy->current_sprite + 1) % 3;
		enemy->remaining_shots_angle = SHOTS_FOR_ANGLE;
		enemy->shot_frames_wait = FRAMES_WAIT_BETWEEN_ANGLES;
	}
}

/* ------------------------------------------------------------ */
void move_all_enemies_projectiles(Enemy* enemies, int index_enemy)
/* ------------------------------------------------------------ */
{
	int i;

	for(i = 0 ; i < index_enemy ; i++)
		if(enemies[i].nature == CANNON)
			move_projectiles(&(enemies[i].projectiles));
}

/* ---------------------------------------------------------- */
void add_projectiles_to_enemies(Enemy* enemies, int index_enemy)
/* ---------------------------------------------------------- */
{
	int i;
	
	for(i = 0 ; i < index_enemy ; i++)
		if(enemies[i].nature == CANNON)
			enemy_add_projectile(&(enemies[i]));
}