#include "../include/game.h"
#include <MLV/MLV_all.h>
#include <time.h>
#include <signal.h>


void handle_sigint(int sig){
	free_everything();
	exit(EXIT_SUCCESS);
}


int main(int argc, char const *argv[])
{
	Game game;
	MLV_Keyboard_button key;

	srand(time(NULL));

	MLV_create_window("oui", "oui", WINDOW_WIDTH, WINDOW_HEIGHT);

	MLV_init_audio();
	load_all_data();

	signal(SIGINT, handle_sigint);

	do {
		init_game(&game);

		main_loop(&game);

		draw_end_screen();

		MLV_play_music(game_over, 1, 1);

		while(key != MLV_KEYBOARD_r && key != MLV_KEYBOARD_q)
			MLV_wait_keyboard(&key, NULL, NULL);

		if(key == MLV_KEYBOARD_r)
			key = 0;
		
		MLV_stop_music();
	}while(key != MLV_KEYBOARD_q);

	free_everything();
	MLV_free_audio();

	return 0;
}