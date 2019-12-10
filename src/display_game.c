#include "../include/display_game.h"


/* --------------------------- */
void draw_stars(Stars* stars)
/* --------------------------- */
{
	int i;

	for(i = 0 ; i < MAX_STAR ; i++)
		MLV_draw_filled_circle(stars->x[i], stars->y[i], (stars->size[i])/ 2, MLV_COLOR_WHITE);
}

/* --------------------------- */
void draw_game(Game* game, MLV_Image* img_ship)
/* --------------------------- */
{
	MLV_clear_window(MLV_COLOR_BLACK);
	
	draw_stars(&(game->stars));
	/* draw_projectiles_enemies() */
	draw_enemies(game->enemies, game->index_enemy);
	draw_ship(&(game->player), img_ship);
	draw_projectiles_ship(&(game->player));

	MLV_actualise_window();
}