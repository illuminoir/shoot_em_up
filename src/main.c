#include "../include/game.h"
#include <time.h>


int main(int argc, char const *argv[])
{
	Ship ship;
	Stars stars;

	srand(time(NULL));

	MLV_create_window("oui", "oui", WINDOW_WIDTH, WINDOW_HEIGHT);

	init_ship(&ship);
	init_stars(&stars);

	main_loop(&ship, &stars);

	return 0;
}