#include "../include/display_enemies.h"

/* -------------------------------------------- */
void draw_enemy_projectiles(ShotList* projectiles)
/* -------------------------------------------- */
{
	int i;

	for(i = 0 ; i < projectiles->index; i++)
		MLV_draw_image(cannon_projectile, (int)projectiles->list[i].hb.x_NW, (int)projectiles->list[i].hb.y_NW);
}

/* -------------------------------------- */
void draw_enemies(Enemy* enemies, int index)
/* -------------------------------------- */
{
	int i;

	for(i = 0 ; i < index ; i++){
		/* if the enemy is deactivated */
		if(enemies[i].hb.x_NW == -1)
			continue;
		/* get the sprite depending on the nature */
		switch(enemies[i].nature){
			case PATTERNED : 
				switch(enemies[i].current_sprite){
					case PATTERNED_SPRITE_IDLE : MLV_draw_image(patterned_sprite_idle, (int)enemies[i].hb.x_NW, (int)enemies[i].hb.y_NW); break;
					case PATTERNED_SPRITE_UP : MLV_draw_image(patterned_sprite_up, (int)enemies[i].hb.x_NW, (int)enemies[i].hb.y_NW); break;
					case PATTERNED_SPRITE_DOWN : MLV_draw_image(patterned_sprite_down, (int)enemies[i].hb.x_NW, (int)enemies[i].hb.y_NW); break;
					default: break;
				} break;
			case LONE_PROJECTILE :
				switch(enemies[i].current_sprite){
					case LONE_PROJECTILE_SPRITE_1 : MLV_draw_image(lone_projectile_first, (int)enemies[i].hb.x_NW, (int)enemies[i].hb.y_NW); break;
					case LONE_PROJECTILE_SPRITE_2 : MLV_draw_image(lone_projectile_second, (int)enemies[i].hb.x_NW, (int)enemies[i].hb.y_NW); break;
					default: break;
				} break;
			case CANNON :
				draw_enemy_projectiles(&(enemies[i].projectiles));
				switch(enemies[i].current_sprite){
					case CANNON_IDLE : MLV_draw_image(cannon_idle, (int)enemies[i].hb.x_NW, (int)enemies[i].hb.y_NW); break;
					case CANNON_ANGLE_1 : MLV_draw_image(cannon_angle_1, (int)enemies[i].hb.x_NW, (int)enemies[i].hb.y_NW); break;
					case CANNON_ANGLE_2 : MLV_draw_image(cannon_angle_2, (int)enemies[i].hb.x_NW, (int)enemies[i].hb.y_NW); break;
					default: break;
				} break;
			case SPINNING:
				switch(enemies[i].current_sprite){
					case SPINNING_SPRITE_1 : MLV_draw_image(spinning_sprite_1, (int)enemies[i].hb.x_NW, (int)enemies[i].hb.y_NW); break;
					case SPINNING_SPRITE_2 : MLV_draw_image(spinning_sprite_2, (int)enemies[i].hb.x_NW, (int)enemies[i].hb.y_NW); break;
					case SPINNING_SPRITE_3 : MLV_draw_image(spinning_sprite_3, (int)enemies[i].hb.x_NW, (int)enemies[i].hb.y_NW); break;
					case SPINNING_SPRITE_4 : MLV_draw_image(spinning_sprite_4, (int)enemies[i].hb.x_NW, (int)enemies[i].hb.y_NW); break;
					default: break;
				} break;
			default: break;
		}
	}
}