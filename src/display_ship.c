#include "../include/display_ship.h"

/* -------------------------------- */
void draw_projectiles_ship(Ship* ship)
/* -------------------------------- */
{
	int i;

	/* draw every projectile if they're active */
	for(i = 0 ; i < ship->projectiles.index ; i++){
		if(!(ship->projectiles.active[i]))
			continue;
		if(ship->has_laser)
			MLV_draw_image(ship_laser, ship->projectiles.list[i].hb.x_NW, ship->projectiles.list[i].hb.y_NW);
		else
			MLV_draw_image(ship_projectile, ship->projectiles.list[i].hb.x_NW, ship->projectiles.list[i].hb.y_NW);
	}
	/* draw the option's projectiles) */
	if(ship->has_option){
		for(i = 0 ; i < ship->option.projectiles.index ; i++){
			if(!(ship->option.projectiles.active[i]))
				continue;
			if(ship->has_laser)
				MLV_draw_image(ship_laser, ship->option.projectiles.list[i].hb.x_NW, ship->option.projectiles.list[i].hb.y_NW);
			else
				MLV_draw_image(ship_projectile, ship->option.projectiles.list[i].hb.x_NW, ship->option.projectiles.list[i].hb.y_NW);
		}
	}
}

/* -------------------- */
void draw_ship(Ship* ship)
/* -------------------- */
{
	/* draw the ship with the correct sprite */
	switch(ship->current_sprite){
		case IDLE : MLV_draw_image(ship_idle, ship->hb.x_NW, ship->hb.y_NW); break;
		case MOVING_UP : MLV_draw_image(ship_moving_up, ship->hb.x_NW, ship->hb.y_NW); break;
		case MOVING_DOWN : MLV_draw_image(ship_moving_down, ship->hb.x_NW, ship->hb.y_NW); break;
		default: break;
	}
	/* if has option upgrade, draw it too */
	if(ship->has_option && ship->option.x != -1){
		switch(ship->option.current_sprite){
			case OPTION_SPRITE_1 : MLV_draw_image(ship_option_1, ship->option.x, ship->option.y); break;
			case OPTION_SPRITE_2 : MLV_draw_image(ship_option_2, ship->option.x, ship->option.y); break;
			default: break;
		}
	}
}