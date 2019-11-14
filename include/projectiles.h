#ifndef __PROJECTILE__
#define __PROJECTILE__

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

typedef struct tir{
	int x;
	int y;
	int speed;
	int vect_x; 
	int vect_y;
}Tir;

Tir AlloueTir();

#endif