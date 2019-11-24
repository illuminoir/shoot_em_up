#ifndef __ENEMY__
#define __ENEMY__

#include "../include/projectiles.h"

typedef struct enemy{
	int x;
	int y;
	int vitesse;
	int nature; /* the type of enemy */
	int current_sprite; /* the current sprite for display */
	ShotList projectiles;
}Enemy;

Enemy InitEnemy(int x, int y);

void MoveEnemy(Enemy *enemy);

void TirEnemy(Enemy enemy);

#endif