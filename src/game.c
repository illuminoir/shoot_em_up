#include "../include/game.h"

/* -------------------- */
void init_game(Game* game)
/* -------------------- */
{
	init_ship(&(game->player));
	init_stars(&(game->stars));
	game->enemies = (Enemy *)malloc(sizeof(Enemy) * ENEMY_MAX_CAPACITY);
	game->index_enemy = 0;
	game->wait_enemy_spawn = 0;

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

/* ----------------------------------------------------- */
void arrange_list_enemies(Enemy* enemies, int* index_enemy)
/* ----------------------------------------------------- */
{
	int i;

	/* sort the enemies by their coordinates */
	qsort(enemies, ENEMY_MAX_CAPACITY, sizeof(Enemy), compare_enemy);

	/* find the first inactive enemy */
	for(i = 0 ; enemies[i].hb.x_NW != -1 ; i++)
		;

	/* the index becomes the first inactive enemy */
	*index_enemy = i;
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
	/* set a random nature for the new generated enemy */
	game->enemies[game->index_enemy].nature = rand() % 4;

	/* initialize the new enemy */
	init_enemy(&(game->enemies[game->index_enemy]));

	/* increase the index */
	game->index_enemy++;

	/* if the list of enemies is full, arrange it */
	if(game->index_enemy == ENEMY_MAX_CAPACITY)
		arrange_list_enemies(game->enemies, &(game->index_enemy));

	/* set the wait time until new enemy generation */
	game->wait_enemy_spawn = WAIT_ENEMY_SPAWN;
}

/* ---------------------------------------- */
int get_ship_event(Ship* ship, int* x, int* y)
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

		return 0;
}

/* ------------------------------- */
void check_all_collisions(Game* game)
/* ------------------------------- */
{
	int i, j, k;

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
			for(j = 0 ; j < game->enemies[i].projectiles.index ; j++)
				if(collision_hitboxes(game->player.hb, game->enemies[i].projectiles.list[j].hb))
					collision_ship_enemy_projectile(&(game->player), &(game->enemies[i].projectiles), j);
		}
		/* check for collisions with the enemy */
		if(collision_hitboxes(game->player.hb, game->enemies[i].hb))
			collision_ship_enemy(&(game->player), &(game->enemies[i]));
		/* check to see if the ship's projectiles hit the enemy */
		for(k = 0 ; k < game->player.projectiles.index ; k++){
			/* if the projectile is inactive */
			if(game->player.projectiles.list[k].hb.x_NW == -1)
				continue;
			/* check for collision between the enemy and the ship's projectiles */
			if(collision_hitboxes(game->player.projectiles.list[k].hb, game->enemies[i].hb))
				collision_ship_projectile_enemy(&(game->player.projectiles), k, &(game->enemies[i]));
		}
	}
}

/* ---------------------------------------------------- */
void move_all_entities(Game* game, int move_x, int move_y)
/* ---------------------------------------------------- */
{
		move_ship(&(game->player), move_x, move_y);
		move_all_enemies(game->enemies, game->index_enemy);
		move_ship_projectiles(&(game->player));
		/* move_enemy_projectiles() */
		move_stars(&(game->stars));
}

/* -------------------- */
void main_loop(Game* game)
/* -------------------- */
{
	struct timespec new, last;
	double accum;
	int move_x, move_y;
	MLV_Image* img_ship;

	/* Main loop over the frames... */
	while(game->player.health){
		move_x = 0; move_y = 0;

		/* Get the time in nanosecond at the frame beginning */
		clock_gettime(CLOCK_REALTIME, &last);

		load_sprite_ship(&(game->player), &img_ship);
		actualize_frames_ship(&(game->player));

		/* Display of the current frame */
		/* THIS FUNCTIONS CALLS MLV_actualise_window A SINGLE TIME */
		draw_game(game, img_ship);

		/* We get here at most one keyboard event each frame */
		/* Event resolution here... */
		if(get_ship_event(&(game->player), &move_x, &move_y))
			break;

		generate_enemy(game);

		/* Moves of the entities on the board */
		move_all_entities(game, move_x, move_y);

		/* Collision resolutions */
		check_all_collisions(game);
			;

		/* Get the time in nanosecond at the frame ending */
		clock_gettime(CLOCK_REALTIME, &new);
		/* We compute the time for the current frame */
		accum = (new.tv_sec - last.tv_sec) + ((new.tv_nsec - last.tv_nsec) / BILLION);

		/* Force wait if the frame was too short */
		if(accum < (1.0 / 60.0))
			MLV_wait_milliseconds((int)((1.0 / 60.0) - accum * 1000));
	}
}