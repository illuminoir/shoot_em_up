#ifndef __ENEMY__
#define __ENEMY__

#include "../include/projectiles.h"


typedef struct _Pattern{
	int vect_x;
	int vect_y;
	int frames_remaining;
}Pattern;

typedef struct enemy{
	Hitbox hb;
	int nature; /* the type of enemy that gives the pattern */
	int vitesse; /* depends on nature as well */
	Pattern* moves; /* amount of patterns depends on nature */
	int current_sprite; /* the current sprite for display */
	ShotList projectiles; /* possibly null depending on nature */
}Enemy;

Enemy InitEnemy(int x, int y);

void MoveEnemy(Enemy *enemy);

void TirEnemy(Enemy enemy);

#endif