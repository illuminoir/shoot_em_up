#include "../include/projectiles.h"

/* ----------------------- */
void init_stars(Stars* stars)
/* ----------------------- */
{
	int i;

	for(i = 0 ; i < MAX_STAR ; i++){
		stars->x[i] = rand() % WINDOW_WIDTH;
		stars->y[i] = rand() % WINDOW_HEIGHT;
		stars->size[i] = (rand() % 6) + 2;
		stars->speed = 1;
	}

}

/* ----------------------- */
void move_stars(Stars* stars)
/* ----------------------- */
{
	int i;

	for(i = 0 ; i < MAX_STAR ; i++){
		stars->x[i] -= stars->speed;
		if(stars->x[i] <= 0){
			stars->x[i] = WINDOW_WIDTH;
			stars->y[i] = rand() % WINDOW_HEIGHT;
		}
	}
}


/* ---------------------- */
ShotList allocate_shotList()
/* ---------------------- */
{
	ShotList tmp;

	tmp.list = (Shot *)malloc(sizeof(Shot) * MAX_CAPACITY);
	if(!(tmp.list))
		;

	tmp.index = 0;
	tmp.capacity = MAX_CAPACITY;

	tmp.active = (int*)malloc(sizeof(int) * MAX_CAPACITY);
	if(!(tmp.active))
		; 

	return tmp;

}