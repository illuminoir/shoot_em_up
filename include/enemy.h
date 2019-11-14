#ifndef __ENEMY__
#define __ENEMY__

#include "../include/projectiles.h"

typedef struct enemy{
	int x;
	int y;
	int vitesse;
	Tir *tir;
}Enemy;

Enemy InitEnemy(int x, int y);

void MoveEnemy(Enemy *enemy);

void TirEnemy(Enemy enemy);

#endif