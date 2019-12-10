#include "../include/game.h"
#include <time.h>


int main(int argc, char const *argv[])
{
	Game game;

	srand(time(NULL));

	MLV_create_window("oui", "oui", WINDOW_WIDTH, WINDOW_HEIGHT);

	init_game(&game);

	main_loop(&game);

	return 0;
}