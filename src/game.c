#include "../include/game.h"


/* --------------------------- */
void main_loop(Ship* ship) /* besoin de rajouter la liste d'ennemis en parametre */
/* --------------------------- */
{
	struct timespec new, last;
	MLV_Event event;
	MLV_Keyboard_button key_sym;
	double accum;
	int quit, move_x, move_y;

	quit = 0;

	/* Main loop over the frames... */
	while(!quit){
		move_x = 0; move_y = 0;
		/* Get the time in nanosecond at the frame beginning */
		clock_gettime(CLOCK_REALTIME, &last);

		/* Display of the current frame */
		/* THIS FUNCTIONS CALLS MLV_actualise_window A SINGLE TIME */
		/* draw_window(&param, &grid); */

		/* We get here at most one keyboard event each frame */
		event = MLV_get_event(&key_sym, NULL, NULL, NULL, NULL,
						 	NULL, NULL, NULL, NULL);

		/* Event resolution here... */
		switch(key_sym){
			case MLV_KEYBOARD_ESCAPE : quit = 1; break;
			case MLV_KEYBOARD_LEFT   : move_x -= 1;
			case MLV_KEYBOARD_RIGHT  : move_x += 1;
			case MLV_KEYBOARD_UP   	 : move_y -= 1;
			case MLV_KEYBOARD_DOWN   : move_y += 1;
			case MLV_KEYBOARD_SPACE  : /* add_projectile(s, ?, ?) ? - a droite du ship */
			default: break;
		}
		/* Moves of the entities on the board */
			move_ship(ship, move_x, move_y);
			/* move_all_enemies() */
			/* move_ship_projectiles() */
			/* move_enemy_projectiles() */
		/* Collision resolutions */
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