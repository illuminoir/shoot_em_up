#include "../include/game.h"


/* ---------------------------------------- */
int get_ship_event(Ship* ship, int* x, int* y)
/* ---------------------------------------- */
{
		
		if(MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED) return 1;

		if(MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED) *x -= 1;

		if(MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED) *x += 1;

		if(MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED) *y -= 1;

		if(MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED) *y += 1;

		if(MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED)
			add_projectile(ship, ship->hb.x_SE + 5, ship->hb.y_NW + (SHIP_SIZE / 2), 3, 1, 0);

		return 0;
}


/* ---------------------------------- */
void main_loop(Ship* ship, Stars* stars) /* besoin de rajouter la liste d'ennemis en parametre */
/* ---------------------------------- */
{
	struct timespec new, last;
	double accum;
	int move_x, move_y;
	MLV_Image* img_ship;

	/* Main loop over the frames... */
	while(1){
		move_x = 0; move_y = 0;

		load_sprite_ship(ship, &img_ship);
		actualize_frames_ship(ship);

		/* Get the time in nanosecond at the frame beginning */
		clock_gettime(CLOCK_REALTIME, &last);

		/* Display of the current frame */
		/* THIS FUNCTIONS CALLS MLV_actualise_window A SINGLE TIME */
		draw_game(ship, img_ship, stars);

		/* We get here at most one keyboard event each frame */
		/* Event resolution here... */
		if(get_ship_event(ship, &move_x, &move_y))
			break;

		/* Moves of the entities on the board */
		move_ship(ship, move_x, move_y);
		/* move_all_enemies() */
		move_ship_projectiles(ship);
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