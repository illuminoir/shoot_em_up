#include "../include/projectiles.h"


/* --------------------------- */
ShotList allocate_shotList()
/* --------------------------- */
{
	ShotList tmp;

	tmp.list = (Shot *)malloc(sizeof(Shot) * MAX_CAPACITY);
	if(!(tmp.list))
		;

	tmp.debut = 0;
	tmp.fin = 0;
	tmp.capacite = MAX_CAPACITY;

	return tmp;

}