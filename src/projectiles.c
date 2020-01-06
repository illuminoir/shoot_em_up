#include "../include/projectiles.h"

/* ----------------------- */
void init_stars(Stars* stars)
/* ----------------------- */
{
	int i;

	for(i = 0 ; i < MAX_STAR ; i++){
		stars->x[i] = rand() % WINDOW_WIDTH;
		stars->y[i] = rand() % WINDOW_HEIGHT;
		stars->size[i] = (rand() % 4) + 2;
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

	return sb->hb.x_NW - sa->hb.x_NW;
}

/* ---------------------------------------- */
void arrange_list_projectiles(ShotList* shots)
/* ---------------------------------------- */
{
	int i;

	/* sort the list by the projectiles' coordinates */
	qsort(shots->list, MAX_CAPACITY_PROJECTILES, sizeof(Shot), compare_pos);

	/* find the first inactive and set the index to that position */
	for(i = 0 ; shots->list[i].hb.x_NW != -1.0 && i < shots->capacity ; i++)
		shots->active[i] = 1;
	shots->index = i;

	/* reset the booleans for the free space */
	for(i = shots->index ; i < shots->capacity ; i++)
		shots->active[i] = 0;

}

/* -------------------------------------- */
void move_projectiles(ShotList* projectiles)
/* -------------------------------------- */
{
	int i;

	for(i = 0 ; i < projectiles->index ; i++){
		/* if the projectile isn't active */
		if(!(projectiles->active[i]))
			continue;

		/* move the projectile's hitbox */
		projectiles->list[i].hb.x_NW += projectiles->list[i].speed * projectiles->list[i].vect_x;
		projectiles->list[i].hb.x_SE += projectiles->list[i].speed * projectiles->list[i].vect_x;
		projectiles->list[i].hb.y_NW += projectiles->list[i].speed * projectiles->list[i].vect_y;
		projectiles->list[i].hb.y_SE += projectiles->list[i].speed * projectiles->list[i].vect_y;

		/* if the projectile goes out of bounds, remove it */
		if(projectiles->list[i].hb.x_NW > WINDOW_WIDTH){
			projectiles->active[i] = 0;
			projectiles->list[i].hb.x_NW = -1;
			projectiles->list[i].hb.y_NW = -1;
		}
	}
}

/* --------------------------------------------------------------------------------------------------------------------- */
void add_projectile(ShotList* projectiles, int x_NW, int y_NW, int x_SE, int y_SE, float speed, float vect_x, float vect_y)
/* --------------------------------------------------------------------------------------------------------------------- */
{
	/* if the list is full arrange it */
	if(projectiles->index == projectiles->capacity)
		arrange_list_projectiles(projectiles);

	/* if the arranged list is still full, wait and don't add a new one */
	if(projectiles->index == projectiles->capacity)
		return;

	/* initialize the new projectile */
	projectiles->list[projectiles->index].hb.x_NW = x_NW;
	projectiles->list[projectiles->index].hb.y_NW = y_NW;
	projectiles->list[projectiles->index].hb.x_SE = x_SE;
	projectiles->list[projectiles->index].hb.y_SE = y_SE;
	projectiles->list[projectiles->index].speed = speed;
	projectiles->list[projectiles->index].vect_x = vect_x;
	projectiles->list[projectiles->index].vect_y = vect_y;

	projectiles->active[projectiles->index] = 1;
	projectiles->index++;
}