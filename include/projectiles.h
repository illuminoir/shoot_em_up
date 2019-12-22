#ifndef __PROJECTILE__
#define __PROJECTILE__
#include <stdio.h>
#include <stdlib.h>
#include "../include/loading.h"

#define MAX_CAPACITY_PROJECTILES 50

#define MAX_STAR 100

/* a hitbox is a square which we represent by saving the coordinates
 * of its North-West and South-East corners and all the points in between
 * those two are considered within the hitbox. */
typedef struct _hitbox {
	float x_NW; /* x of the North-West corner */
	float y_NW; /* y of the North-West corner */
	float x_SE; /* x of the South-East corner */
	float y_SE; /* y of the South-East corner */
}Hitbox;

typedef struct _stars{
	int x[MAX_STAR]; /* x coordinate for each star */
	int y[MAX_STAR]; /* y coordinate for each star */
	int size[MAX_STAR]; /* size in pixel */
	int speed; /* moving speed of the stars */
}Stars;

typedef struct tir{
	Hitbox hb; /* projectile's hitbox */
	float speed; /* projectile's speed */
	float vect_x; /* float so that we are not restricted to "square" angles */
	float vect_y; /* same */
}Shot;

/* A list of shots is represented as a list with a capacity and an index, we keep on adding values to it until
 * index reaches capacity and when it is so we arrange it. Arrangement sorts the list so that the
 * inactive shots are put behind and we change the index so that there is free room again */
typedef struct _shotList{
	Shot* list; /* malloc capacite * tirs qui sera le nb max de tirs possible a l'ecran (le calculer) */
	int index;
	int capacity;
	int* active;
}ShotList;

/* Moves the background stars.
 * The stars are moved from right to left and when they reach the left border,
 * they are moved to the far right with a new y coordinate.
 * Parameters : 
 *		Stars* stars : pointer to the structure representing the stars */
void move_stars(Stars* stars);


/* Initializes the background stars.
 * The stars are represented by a x, y and size value unique to each stars.
 * Parameters : 
 *		Stars* stars : pointer to the structure representing the stars */
void init_stars(Stars* stars);

/* Allocates a list of projectiles for the different entities
 * The list works with a maximum capacity, an index and a list of capacity booleans. Everytime a new projectile is added
 * the index goes up by 1. Whenever we remove a projectile, set it to inactive in the list of booleans and its coordinates
 * to -1. When it's full (when index equals capacity), sort it to have all the inactives ones after the active ones
 * and then set index to the last active one.
 * Parameters : none
 * Return : the allocated list */
ShotList allocate_shotList();

/* comparison function for qsort function called in arrange_list_projectiles() */
int compare_pos(const void* a, const void* b);

/* Arranges the list when "full" i.e. when index equals capacity.
 * arrangement is done so : sort the projectiles by their coordinates (all the inactive ones having -1 as coordinates),
 * go through the list until finding a projectile that is inactive, this becomes the new index for the list and
 * all the values from index to the end of the list become free.
 * Parameters :
 * 		ShotList* shots : pointer to the list to arrange */
void arrange_list_projectiles(ShotList* shots);

/* Moves all the projectiles for the given list of projectiles.
 * If the list is full, arrange it by calling arrange_list_projectiles().
 * Parameters :
 *		ShotList* projectiles : the list of projectiles to move. */
void move_projectiles(ShotList* projectiles);

/* Adds a projectile to the given list of projectiles.
 * Parameters :
 *		ShotList* projectiles : the list of projectiles
 *		int x_NW			  : north-west corner x position for the new projectile
 *		int y_NW			  : north-west corner y position for the new projectile
 *		int x_SE			  : south-east corner x position for the new projectile
 *		int y_SE			  : south-east corner y position for the new projectile
 *		float speed			  : speed of the projectile
 *		float vect_x		  : x vector of the projectile
 *		float vect_y 		  : y vector of the projectile */
void add_projectile(ShotList* projectiles, int x_NW, int y_NW, int x_SE, int y_SE, float speed, float vect_x, float vect_y);

#endif