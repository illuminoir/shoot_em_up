#ifndef __PROJECTILE__
#define __PROJECTILE__
#include <stdio.h>
#include <stdlib.h>


#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define MAX_CAPACITY 100

#define MAX_STAR 100

/* a hitbox is a square which we represent by saving the coordinates
 * of its North-West and South-East corners and all the points in between
 * those two are considered within the hitbox. */
typedef struct _hitbox {
	int x_NW; /* x of the North-West corner */
	int y_NW; /* y of the North-West corner */
	int x_SE; /* x of the South-East corner */
	int y_SE; /* y of the South-East corner */
}Hitbox;

typedef struct _stars{
	int x[MAX_STAR];
	int y[MAX_STAR];
	int size[MAX_STAR]; /* size in pixel */
	int speed; /* moving speed of the stars */
}Stars;

typedef struct tir{
	int x;
	int y;
	int speed;
	float vect_x; /* float so that we are not restricted to "square" angles */
	float vect_y; /* same */
}Shot;

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
 * -----------------(how the list is)----------------------------
 * Parameters : none
 * Return : the allocated list */
ShotList allocate_shotList();

#endif