#ifndef __PROJECTILE__
#define __PROJECTILE__

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define MAX_CAPACITY 100

#include <stdio.h>
#include <stdlib.h>

typedef struct tir{
	int x;
	int y;
	int speed;
	int vect_x; 
	int vect_y;
}Shot;

typedef struct _shotList{
	Shot* list; /* malloc capacite * tirs qui sera le nb max de tirs possible a l'ecran (le calculer) */
	int debut;
	int fin;
	int capacite;
}ShotList;

ShotList allocate_shotList();

#endif