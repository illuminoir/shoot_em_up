#include "../include/display_enemies.h"


/* ----------------------------------------------------------- */
void get_sprite_patterned(MLV_Image** sprite, int current_sprite)
/* ----------------------------------------------------------- */
{
	/* load the correct sprite depending on the enemy's movement */
	switch(current_sprite){
		case PATTERNED_SPRITE_IDLE : *sprite = MLV_load_image("img/enemy_sprite_1.png"); break;
		case PATTERNED_SPRITE_UP : *sprite = MLV_load_image("img/enemy_sprite_2.png"); break;
		case PATTERNED_SPRITE_DOWN : *sprite = MLV_load_image("img/enemy_sprite_3.png"); break;
		default: break;
	}

	/* resize the loaded sprite */
	MLV_resize_image_with_proportions(*sprite, PATTERNED_SIZE, PATTERNED_SIZE);
}

/* ----------------------------------------------------------------- */
void get_sprite_lone_projectile(MLV_Image** sprite, int current_sprite)
/* ----------------------------------------------------------------- */
{
	/* load the correct sprite depending on the enemy's movement */
	switch(current_sprite){
		case LONE_PROJECTILE_SPRITE_1 : *sprite = MLV_load_image("img/enemy_lone_shot_1.png"); break;
		case LONE_PROJECTILE_SPRITE_2 : *sprite = MLV_load_image("img/enemy_lone_shot_2.png"); break;
	}

	/* resize the loaded sprite */
	MLV_resize_image_with_proportions(*sprite, LONE_PROJECTILE_SIZE, LONE_PROJECTILE_SIZE);
}

/* -------------------------------------------------------- */
void get_sprite_cannon(MLV_Image** sprite, int current_sprite)
/* -------------------------------------------------------- */
{
	/* load the correct sprite depending on the enemy's movement */
	switch(current_sprite){
		case CANNON_IDLE : *sprite = MLV_load_image("img/cannon_sprite_1.png"); break;
		case CANNON_ANGLE_1 : *sprite = MLV_load_image("img/cannon_sprite_2.png"); break;
		case CANNON_ANGLE_2 : *sprite = MLV_load_image("img/cannon_sprite_3.png"); break;
	}

	/* resize the loaded sprite */
	MLV_resize_image_with_proportions(*sprite, CANNON_SIZE, CANNON_SIZE);
}

/* ---------------------------------------------------------- */
void get_sprite_spinning(MLV_Image** sprite, int current_sprite)
/* ---------------------------------------------------------- */
{
	/* load the correct sprite depending on the enemy's movement */
	switch(current_sprite){
		case SPINNING_SPRITE_1 : *sprite = MLV_load_image("img/spinning_enemy_sprite_1.png"); break;
		case SPINNING_SPRITE_2 : *sprite = MLV_load_image("img/spinning_enemy_sprite_2.png"); break;
		case SPINNING_SPRITE_3 : *sprite = MLV_load_image("img/spinning_enemy_sprite_3.png"); break;
		case SPINNING_SPRITE_4 : *sprite = MLV_load_image("img/spinning_enemy_sprite_4.png"); break;
	}

	/* resize the loaded sprite */
	MLV_resize_image_with_proportions(*sprite, SPINNING_SIZE, SPINNING_SIZE);
}


/* -------------------------------------- */
void draw_enemies(Enemy* enemies, int index)
/* -------------------------------------- */
{
	int i;
	MLV_Image* sprite;

	for(i = 0 ; i < index ; i++){
		/* if the enemy is deactivated */
		if(enemies[i].hb.x_NW == -1)
			continue;
		/* get the sprite depending on the nature */
		switch(enemies[i].nature){
			case PATTERNED : get_sprite_patterned(&sprite, enemies[i].current_sprite); break;
			case LONE_PROJECTILE : get_sprite_lone_projectile(&sprite, enemies[i].current_sprite); break;
			case CANNON : get_sprite_cannon(&sprite, enemies[i].current_sprite); break;
			case SPINNING: get_sprite_spinning(&sprite, enemies[i].current_sprite); break;
			default: break;
		}
		/* draw the sprite */
		MLV_draw_image(sprite, (int)enemies[i].hb.x_NW, (int)enemies[i].hb.y_NW);
	}
}