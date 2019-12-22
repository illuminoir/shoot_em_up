#include "../include/game.h"
#include <time.h>
#include <signal.h>


void handle_sigint(int sig){
	free_everything();
	exit(EXIT_SUCCESS);
}


int main(int argc, char const *argv[])
{
	Game game;

	srand(time(NULL));

	signal(SIGINT, handle_sigint);

	MLV_create_window("oui", "oui", WINDOW_WIDTH, WINDOW_HEIGHT);

	init_game(&game);

	main_loop(&game);

	return 0;
}