#include "../include/game.h"


/* --------------------------- */
int get_ship_event(MLV_Keyboard_button key, MLV_Button_state state, int* x, int* y)
/* --------------------------- */
{
		if(key == MLV_KEYBOARD_ESCAPE) return 1;

		if((key == MLV_KEYBOARD_LEFT) && (state == MLV_PRESSED)) *x = -1;
		else if((key == MLV_KEYBOARD_LEFT) && (state == MLV_RELEASED)) *x = 0;


		if((key == MLV_KEYBOARD_RIGHT) && (state == MLV_PRESSED)) *x = 1;
		else if((key == MLV_KEYBOARD_RIGHT) && (state == MLV_RELEASED)) *x = 0;

		if((key == MLV_KEYBOARD_UP) && (state == MLV_PRESSED)) *y = -1;
		else if((key == MLV_KEYBOARD_UP) && (state == MLV_RELEASED)) *y = 0;

		if((key == MLV_KEYBOARD_DOWN) && (state == MLV_PRESSED)) *y = 1;
		else if((key == MLV_KEYBOARD_DOWN) && (state == MLV_RELEASED)) *y = 0;

		if(key == MLV_KEYBOARD_SPACE){ /* add_projectile(s, ?, ?) ? - a droite du ship */ }

		return 0;
}


/* --------------------------- */
void main_loop(Ship* ship, Stars* stars) /* besoin de rajouter la liste d'ennemis en parametre */
/* --------------------------- */
{
	struct timespec new, last;
	MLV_Event event;
	MLV_Keyboard_button key;
	MLV_Button_state state;
	double accum;
	int quit, move_x, move_y;
	MLV_Image* img_ship;

	quit = 0;

	move_x = 0; move_y = 0;

	/* Main loop over the frames... */
	while(!quit){
		load_sprite_ship(ship, &img_ship);
		/* Get the time in nanosecond at the frame beginning */
		clock_gettime(CLOCK_REALTIME, &last);

		/* Display of the current frame */
		/* THIS FUNCTIONS CALLS MLV_actualise_window A SINGLE TIME */
		MLV_clear_window(MLV_COLOR_BLACK);
		/* draw_window(&param, &grid); */
		draw_game(ship, img_ship, stars);
		MLV_actualise_window();

		/* We get here at most one keyboard event each frame */
		event = MLV_get_event(&key, NULL, NULL, NULL, NULL,
						 	NULL, NULL, NULL, &state);

		/* Event resolution here... */
		if(get_ship_event(key, state, &move_x, &move_y))
			break;


		/* Moves of the entities on the board */
			move_ship(ship, move_x, move_y);
			/* move_all_enemies() */
			/* move_ship_projectiles() */
			/* move_enemy_projectiles() */
			move_stars(stars);
		/* Collision resolutions */
			;

		/* Get the time in nanosecond at the frame ending */
		clock_gettime(CLOCK_REALTIME, &new);
		/* We compute the time for the current frame */
		accum = (new.tv_sec - last.tv_sec) + ((new.tv_nsec - last.tv_nsec) / BILLION);

		/* Force wait if the frame was too short */
		if(accum < (1.0 / 10.0))
			MLV_wait_milliseconds((int)((1.0 / 10.0) - accum * 1000));
	}
}