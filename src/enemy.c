#include "../include/enemy.h"
#include <assert.h>

/*
Enemy InitEnemy(int x, int y){
	Enemy enemy;
	enemy.x = x;
	enemy.y = y;
	/*enemy.tir = ;*/
/*	enemy.vitesse = 1;
	return enemy;
}*/
/*
void MoveEnemy(Enemy *enemy){
	assert(enemy != NULL);

	while((enemy->x) >= 0){
		enemy->x -= enemy->vitesse;
	}
}
*/
void TirEnemy(Enemy enemy){

}

void AddVitesse(Enemy *enemy, int vitesse){
	enemy->vitesse = vitesse;
}