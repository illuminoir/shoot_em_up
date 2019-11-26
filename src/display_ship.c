#include "../include/display_ship.h"


/* --------------------------- */
void load_sprite_ship(Ship* ship, MLV_Image** img)
/* --------------------------- */
{
	switch(ship->current_sprite){
		case IDLE : *img = MLV_load_image("img/ship_idle.png"); break;
		case MOVING_UP : *img = MLV_load_image("img/ship_moving_up.png"); break;
		case MOVING_DOWN : *img = MLV_load_image("img/ship_moving_down.png"); break;
		default: break;
	}
	MLV_resize_image_with_proportions(*img, SHIP_SIZE, SHIP_SIZE);	
}


void draw_ship(Ship* ship, MLV_Image* img){
	MLV_draw_image(img, ship->x, ship->y);
}