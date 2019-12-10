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

	/* allocate the list of shots */
	tmp.list = (Shot *)malloc(sizeof(Shot) * MAX_CAPACITY_PROJECTILES);
	if(!(tmp.list))
		;

	tmp.index = 0;
	tmp.capacity = MAX_CAPACITY_PROJECTILES;

	/* allocate the list of booleans */
	tmp.active = (int*)calloc(MAX_CAPACITY_PROJECTILES, sizeof(int));
	if(!(tmp.active))
		; 

	return tmp;

}

/* --------------------------------------- */
int compare_pos(const void* a, const void* b)
/* --------------------------------------- */
{
	Shot* sa = (Shot *)a;
	Shot* sb = (Shot *)b;

	return sa->hb.x_NW - sb->hb.x_NW;
}

/* --------------------------------------------- */
void arrange_list_projectiles(ShotList* shots)
/* --------------------------------------------- */
{
	int i;

	/* sort the list by the projectiles' coordinates */
	qsort(shots->list, MAX_CAPACITY_PROJECTILES, sizeof(Shot), compare_pos);

	/* find the first inactive and set the index to that position */
	for(i = 0 ; shots->list[i].hb.x_NW != -1 ; i++)
		shots->active[i] = 1;
	shots->index = i;

	/* reset the booleans for the free space */
	for(i = shots->index ; i < shots->capacity ; i++)
		shots->active[i] = 0;
}