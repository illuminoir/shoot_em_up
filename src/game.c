#include "../include/game.h"

/* -------------------- */
void init_game(Game* game)
/* -------------------- */
{
	init_ship(&(game->player));
	init_stars(&(game->stars));
	game->enemies = (Enemy *)calloc(sizeof(Enemy), ENEMY_MAX_CAPACITY);
	game->bonuses = (Bonus *)calloc(sizeof(Bonus), BONUS_MAX_CAPACITY);
	game->index_enemy = 0;
	game->index_bonus = 0;
	game->current_enemy = 0;
	game->remaining_spawns = 0;
	game->wait_enemy_spawn = 0;
	game->current_bonus = 0;

	/* faire un truc pour faire spawn une lignee comme sur gradius */
	/*if(e->nature == LONE_PROJECTILE)
		;*/
}

/* ----------------------------------------- */
int compare_enemy(const void* a, const void* b)
/* ----------------------------------------- */
{
	Enemy* sa = (Enemy *)a;
	Enemy* sb = (Enemy *)b;

	return sb->hb.x_NW - sa->hb.x_NW;
}

/* ----------------------------------------- */
int compare_bonus(const void* a, const void* b)
/* ----------------------------------------- */
{
	Bonus* ba = (Bonus *)a;
	Bonus* bb = (Bonus *)b;

	return bb->hb.x_NW - ba->hb.x_NW;
}

/* ----------------------------------------------------- */
void arrange_list_enemies(Enemy* enemies, int* index_enemy)
/* ----------------------------------------------------- */
{
	int i;

	/* sort the enemies by their coordinates */
	qsort(enemies, ENEMY_MAX_CAPACITY, sizeof(Enemy), compare_enemy);

	/* find the first inactive enemy */
	for(i = 0 ; enemies[i].hb.x_NW != -1 && i < ENEMY_MAX_CAPACITY ; i++)
		;

	/* the index becomes the first inactive enemy */
	*index_enemy = i;
}

/* ----------------------------------------------------- */
void arrange_list_bonuses(Bonus* bonuses, int* index_bonus)
/* ----------------------------------------------------- */
{
	int i;

	/* sort the bonuses by their coordinates */
	qsort(bonuses, BONUS_MAX_CAPACITY, sizeof(Bonus), compare_bonus);

	/* find the first inactive bonus */
	for(i = 0 ; bonuses[i].hb.x_NW != -1 && i < BONUS_MAX_CAPACITY ; i++)
		;

	/* the index becomes the first inactive bonus */
	*index_bonus = i;
}

/* ------------------------------- */
void get_remaining_spawns(Game* game)
/* ------------------------------- */
{
	switch(game->current_enemy){
		case CANNON : game->remaining_spawns = CANNON_SPAWNS; break;
		case LONE_PROJECTILE : game->remaining_spawns = LONE_SPAWNS; break;
		case PATTERNED : game->remaining_spawns = PATTERNED_SPAWNS; break;
		case SPINNING : game->remaining_spawns = SPINNING_SPAWNS; break;
		default: break;
	}
}

/* ------------------------- */
void generate_enemy(Game* game)
/* ------------------------- */
{
	/* if we can't spawn yet */
	if(game->wait_enemy_spawn){
		game->wait_enemy_spawn--;
		return;
	}

	/* if the list of enemies is full, arrange it */
	if(game->index_enemy == ENEMY_MAX_CAPACITY)
		arrange_list_enemies(game->enemies, &(game->index_enemy));

	if(game->index_enemy == ENEMY_MAX_CAPACITY)
		return;

	if(!(game->remaining_spawns)){
		game->current_enemy = rand() % 4;
		get_remaining_spawns(game);
	}

	game->remaining_spawns--;

	game->enemies[game->index_enemy].nature = game->current_enemy;

	/* initialize the new enemy */
	init_enemy(&(game->enemies[game->index_enemy]));

	/* increase the index */
	game->index_enemy++;

	if(!(game->remaining_spawns))
		game->wait_enemy_spawn = WAIT_ENEMY_SPAWN;
	else
		game->wait_enemy_spawn = WAIT_MULTIPLE_SPAWNS;
}

/* ---------------------------------------- */
void generate_bonus(Game *game, Enemy* enemy)
/* ---------------------------------------- */
{
	int rand_try;

	rand_try = rand() % 100;

	/* try to generate a bonus depending on the drop rate */
	if(rand_try < enemy->drop_rate){
		init_bonus(&(game->bonuses[game->index_bonus]), enemy->hb.x_NW, enemy->hb.y_NW);

		game->index_bonus++;

		/* if the list of bonuses is full */
		if(game->index_bonus == BONUS_MAX_CAPACITY)
			arrange_list_bonuses(game->bonuses, &(game->index_bonus));
	}

	/* set the enemy as dead/inactive */
	enemy->hb.x_NW = -1;
	enemy->hb.y_NW = -1;
}

/* ---------------------------------------- */
int get_ship_event(Ship* ship, int* x, int* y, int* current_bonus)
/* ---------------------------------------- */
{
		/* if escape is pressed, quit the same */
		if(MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED) return 1;

		/* if the left arrow is pressed, move to the left */
		if(MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED) *x -= 1;

		/* if the right arrow is pressed, move to the right */
		if(MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED) *x += 1;

		/* if the up arrow is pressed, move upwards */
		if(MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED) *y -= 1;

		/* if the down arrow is pressed, move downwards */
		if(MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED) *y += 1;

		/* if space is pressed, add a new projectile to the ship */
		if(MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED)
			add_projectile_ship(ship, ship->hb.x_SE + 5, ship->hb.y_NW + (SHIP_SIZE / 2), 3, 1, 0);

		if(MLV_get_keyboard_state(MLV_KEYBOARD_LCTRL) == MLV_PRESSED)
			consume_bonus(current_bonus, ship);

		if(ship->has_missile)
			add_missile_to_ship(ship);

		return 0;
}

/* ------------------------------- */
void check_all_collisions(Game* game)
/* ------------------------------- */
{
	int i, j, k, l, m;

	/* if the player is invulnerable, cannot be hit */
	if(game->player.invulnerability_frames)
		return;

	/* check for all enemies */
	for(i = 0 ; i < game->index_enemy ; i++){
		/* if the enemy is inactive */
		if(game->enemies[i].hb.x_NW == -1)
			continue;
		/* if the enemy is a cannon, check collisions with all of its projectiles */
		if(game->enemies[i].nature == CANNON){
			for(j = 0 ; j < game->enemies[i].projectiles.index ; j++){
				if(!(game->enemies[i].projectiles.active[j]))
					continue;
				if(collision_hitboxes(game->player.hb, game->enemies[i].projectiles.list[j].hb))
					collision_ship_enemy_projectile(&(game->player), &(game->enemies[i].projectiles), j);
			}
		}
		/* check for collisions with the enemy */
		if(collision_hitboxes(game->player.hb, game->enemies[i].hb))
			collision_ship_enemy(&(game->player), &(game->enemies[i]));
		/* check to see if the ship's projectiles hit the enemy */
		for(k = 0 ; k < game->player.projectiles.index ; k++){
			/* if the projectile is inactive */
			if(!(game->player.projectiles.active[k]))
				continue;
			/* check for collision between the enemy and the ship's projectiles */
			if(collision_hitboxes(game->player.projectiles.list[k].hb, game->enemies[i].hb)){
				if(collision_ship_projectile_enemy(&(game->player), k, &(game->enemies[i]))){
					MLV_play_sound(enemy_death, 1.0);/*
					MLV_draw_image(enemy_death_particle, game->enemies[i].hb.x_NW + (CANNON_SIZE / 2) - (MLV_get_image_height(enemy_death_particle) / 2),
						game->enemies[i].hb.y_NW + (CANNON_SIZE / 2) - (MLV_get_image_height(enemy_death_particle) / 2));*/
					generate_bonus(game, &(game->enemies[i]));
					break;
				}
				else
					MLV_play_sound(enemy_hit, 1.0);
				/* ajouter son de hit a tous les autres collisions et ajouteer les draw image a collisions (si mort ou  hit) */
			}
		}
		/* if the player has the option upgrade */
		if(game->player.has_option){
			for(m = 0 ; m < game->player.option.projectiles.index ; m++){
				/* if the projectile is inactive */
				if(!(game->player.option.projectiles.active[m]))
					continue;
				/* check for collision between the option's projectile and the enemy */
				if(collision_hitboxes(game->player.option.projectiles.list[m].hb, game->enemies[i].hb)){
					if(collision_option_projectile_enemy(&(game->player), m, &(game->enemies[i]))){
						MLV_play_sound(enemy_death, 1.0);
						generate_bonus(game, &(game->enemies[i]));
						break;
					}
					else
						MLV_play_sound(enemy_hit, 1.0);
				}
			}
		}
		/* if the player has the missile upgrade */
		if(game->player.has_missile){
			for(m = 0 ; m < game->player.missiles.index ; m++){
				/* if the projectile is inactive or the enemy already died */
				if(!(game->player.missiles.active[m]))
					continue;
				/* check for collision between the missile and the enemy */
				if(collision_hitboxes(game->player.missiles.list[m].hb, game->enemies[i].hb)){
					if(collision_missile_enemy(&(game->player), m, &(game->enemies[i]))){
						MLV_play_sound(enemy_death, 1.0);
						generate_bonus(game, &(game->enemies[i]));
						break;
					}
					else
						MLV_play_sound(enemy_hit, 1.0);
				}
			}
		}
	}
	/* check if the player grabs a bonus */
	for(l = 0 ; l < game->index_bonus ; l++){
		/* if the bonus is inactive */
		if(game->bonuses[l].hb.x_NW == -1)
			continue;
		if(collision_hitboxes(game->player.hb, game->bonuses[l].hb))
			collision_ship_bonus(&(game->current_bonus), game->bonuses, l);
	}
}

/* ---------------------------------------------------- */
void move_all_entities(Game* game, int move_x, int move_y)
/* ---------------------------------------------------- */
{
	move_ship(&(game->player), move_x, move_y);
	move_all_enemies(game->enemies, game->index_enemy);
	move_all_bonuses(game->bonuses, game->index_bonus);
	move_ship_projectiles(&(game->player));
	move_all_enemies_projectiles(game->enemies, game->index_enemy);
	move_stars(&(game->stars));
}

/* --------------------------- */
void actualize_frames(Game* game)
/* --------------------------- */
{
	int i;
	
	actualize_frames_ship(&(game->player));
	
	for(i = 0 ; i < game->index_enemy ; i++)
		actualize_frames_enemy(&(game->enemies[i]));
}

/* -------------------- */
void main_loop(Game* game)
/* -------------------- */
{
	struct timespec new, last;
	double accum;
	int move_x, move_y;

	MLV_play_music(music, 0.2, -1);

	/* Main loop over the frames... */
	while(game->player.health){
		move_x = 0; move_y = 0;

		/* Get the time in nanosecond at the frame beginning */
		clock_gettime(CLOCK_REALTIME, &last);

		actualize_frames(game);

		/* Display of the current frame */
		/* THIS FUNCTIONS CALLS MLV_actualise_window A SINGLE TIME */
		draw_game(game);

		/* We get here at most one keyboard event each frame */
		/* Event resolution here... */
		if(get_ship_event(&(game->player), &move_x, &move_y, &(game->current_bonus)))
			break;

		/* generates an enemy if possible */
		generate_enemy(game);

		/* add projectiles to enemies */
		add_projectiles_to_enemies(game->enemies, game->index_enemy);

		/* Moves of the entities on the board */
		move_all_entities(game, move_x, move_y);

		/* Collision resolutions */
		check_all_collisions(game);

		/* Get the time in nanosecond at the frame ending */
		clock_gettime(CLOCK_REALTIME, &new);
		/* We compute the time for the current frame */
		accum = (new.tv_sec - last.tv_sec) + ((new.tv_nsec - last.tv_nsec) / BILLION);

		/* Force wait if the frame was too short */
		if(accum < (1.0 / 30.0))
			MLV_wait_milliseconds((int)((1.0 / 30.0) - accum * 1000));
	}

	MLV_stop_music();
}