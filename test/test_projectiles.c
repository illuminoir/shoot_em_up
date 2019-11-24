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

ShotList allocate_shotList(){
	ShotList tmp;

	tmp.list = (Shot *)malloc(sizeof(Shot) * MAX_CAPACITY);
	if(!(tmp.list))
		;

	tmp.debut = 0;
	tmp.fin = 0;
	tmp.capacite = MAX_CAPACITY;

	return tmp;

}

void print_shot(Shot* s){
	printf("x : %d\n", s->x);
	printf("y : %d\n", s->y);
	printf("speed : %d\n", s->speed);
	printf("vectx : %d\n", s->vect_x);
	printf("vecty : %d\n", s->vect_y);
}

int main(int argc, char const *argv[])
{
	ShotList S = allocate_shotList();

	if(S.list != NULL)
		printf("Oui !\n");
	S.list[99].x = 1;
	S.list[99].y = 1;

	print_shot(&(S.list[0]));

	return 0;
}