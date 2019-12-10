#include "../include/display_ship.h"


/* -------------------------------------------- */
void load_sprite_ship(Ship* ship, MLV_Image** img)
/* -------------------------------------------- */
{
	/* load the correct sprite depending on the ship's movement */
	switch(ship->current_sprite){
		case IDLE : *img = MLV_load_image("img/ship_idle.png"); break;
		case MOVING_UP : *img = MLV_load_image("img/ship_moving_up.png"); break;
		case MOVING_DOWN : *img = MLV_load_image("img/ship_moving_down.png"); break;
		default: break;
	}
	/* resize the loaded sprite */
	MLV_resize_image_with_proportions(*img, SHIP_SIZE, SHIP_SIZE);	
}

/* -------------------------------- */
void draw_projectiles_ship(Ship* ship)
/* -------------------------------- */
{
	MLV_Image* sprite;
	int i;

	/* load the right sprite depending on the laser upgrade */
	if(ship->has_laser) sprite = MLV_load_image("img/laser_ship.png");
	else sprite = MLV_load_image("img/projectile_ship.png");

	/* resize the sprite to match the rest */
	MLV_resize_image_with_proportions(sprite, PROJECTILE_SIZE, PROJECTILE_SIZE);

	/* draw every projectile if they're active */
	for(i = 0 ; i < ship->projectiles.index ; i++){
		if(!(ship->projectiles.active[i]))
			continue;
		MLV_draw_image(sprite, ship->projectiles.list[i].hb.x_NW, ship->projectiles.list[i].hb.y_NW);
	}

	MLV_free_image(sprite);
}

/* ------------------------------------ */
void draw_ship(Ship* ship, MLV_Image* img)
/* ------------------------------------ */
{
	MLV_draw_image(img, ship->hb.x_NW, ship->hb.y_NW);
}