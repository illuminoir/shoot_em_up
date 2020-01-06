#include "../include/display_game.h"

/* ----------------------- */
void draw_stars(Stars* stars)
/* ----------------------- */
{
	int i;

	for(i = 0 ; i < MAX_STAR ; i++)
		MLV_draw_filled_circle(stars->x[i], stars->y[i], (stars->size[i])/ 2, MLV_COLOR_WHITE);
}

/* ----------------------- */
void draw_options(Game* game)
/* ----------------------- */
{
	/* draw option 1 */
	if(game->current_bonus == 1)
		MLV_draw_image(option1_selected, WINDOW_WIDTH * 3 / 12, WINDOW_HEIGHT * 9 / 10);
	else
		MLV_draw_image(option1, WINDOW_WIDTH * 3 / 12, WINDOW_HEIGHT * 9 / 10);
	/* draw option 2*/
	if(game->current_bonus == 2)
		MLV_draw_image(option2_selected, WINDOW_WIDTH * 4 / 12, WINDOW_HEIGHT * 9 / 10);
	else
		MLV_draw_image(option2, WINDOW_WIDTH * 4 / 12, WINDOW_HEIGHT * 9 / 10);
	/* draw option 3 */
	if(game->current_bonus == 3)
		MLV_draw_image(option3_selected, WINDOW_WIDTH * 5 / 12, WINDOW_HEIGHT * 9 / 10);
	else
		MLV_draw_image(option3, WINDOW_WIDTH * 5 / 12, WINDOW_HEIGHT * 9 / 10);
	/* draw option 4 */
	if(game->current_bonus == 4)
		MLV_draw_image(option4_selected, WINDOW_WIDTH * 6 / 12, WINDOW_HEIGHT * 9 / 10);
	else
		MLV_draw_image(option4, WINDOW_WIDTH * 6 / 12, WINDOW_HEIGHT * 9 / 10);
	/* draw option 5 */
	if(game->current_bonus == 5)
		MLV_draw_image(option5_selected, WINDOW_WIDTH * 7 / 12, WINDOW_HEIGHT * 9 / 10);
	else
		MLV_draw_image(option5, WINDOW_WIDTH * 7 / 12, WINDOW_HEIGHT * 9 / 10);

	/* draw option 6 */
	MLV_draw_image(option6, WINDOW_WIDTH * 8 / 12, WINDOW_HEIGHT * 9 / 10);
}

/* ----------------------- */
void draw_bonuses(Game* game)
/* ----------------------- */
{
	int i;

	for(i = 0 ; i < game->index_bonus ; i++){
		/* if the bonus isn't active */
		if(game->bonuses[i].hb.x_NW == -1)
			continue;
		/* draw the corresponding sprite */
		if(game->bonuses[i].current_sprite == BONUS_FIRST_SPRITE)
			MLV_draw_image(bonus1, (int)game->bonuses[i].hb.x_NW, (int)game->bonuses[i].hb.y_NW);
		else
			MLV_draw_image(bonus2, (int)game->bonuses[i].hb.x_NW, (int)game->bonuses[i].hb.y_NW);
	}
}

/* -------------------- */
void draw_game(Game* game)
/* -------------------- */
{
	MLV_clear_window(MLV_COLOR_BLACK);
	
	draw_stars(&(game->stars));
	draw_enemies(game->enemies, game->index_enemy);
	draw_ship(&(game->player));
	draw_projectiles_ship(&(game->player));
	draw_missiles_ship(&(game->player));
	draw_bonuses(game);
	draw_options(game);


	MLV_actualise_window();
}


/* ---------------- */
void draw_end_screen()
/* ---------------- */
{
	MLV_Image* end_screen = MLV_load_image("img/end_screen.png");

	MLV_clear_window(MLV_COLOR_BLACK);

	MLV_draw_image(end_screen, WINDOW_WIDTH / 2 - (MLV_get_image_width(end_screen) / 2), WINDOW_HEIGHT / 2 - (MLV_get_image_height(end_screen) / 2));

	MLV_actualise_window();

}