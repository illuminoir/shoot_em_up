#include "../include/display_ship.h"


/* -------------------------------------------- */
void load_sprite_ship(Ship* ship, MLV_Image** img)
/* -------------------------------------------- */
{
	switch(ship->current_sprite){
		case IDLE : *img = MLV_load_image("img/ship_idle.png"); break;
		case MOVING_UP : *img = MLV_load_image("img/ship_moving_up.png"); break;
		case MOVING_DOWN : *img = MLV_load_image("img/ship_moving_down.png"); break;
		default: break;
	}
	MLV_resize_image_with_proportions(*img, SHIP_SIZE, SHIP_SIZE);	
}

/* -------------------------------- */
void draw_projectiles_ship(Ship* ship)
/* -------------------------------- */
{
	MLV_Image* sprite;
	int i;

	if(ship->has_laser) sprite = MLV_load_image("img/laser_ship.png");
	else sprite = MLV_load_image("img/projectile_ship.png");

	MLV_resize_image_with_proportions(sprite, 20, 20);

	for(i = 0 ; i < ship->projectiles.index ; i++){
		if(!(ship->projectiles.active[i]))
			continue;
		MLV_draw_image(sprite, ship->projectiles.list[i].x, ship->projectiles.list[i].y);
	}

	MLV_free_image(sprite);
}

/* ------------------------------------ */
void draw_ship(Ship* ship, MLV_Image* img)
/* ------------------------------------ */
{
	MLV_draw_image(img, ship->hb.x_NW, ship->hb.y_NW);
}