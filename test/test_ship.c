#include <stdio.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#define IDLE 0
#define MOVING_UP 1
#define MOVING_DOWN 2
/* #define SPRITE_SIZE ?? */

typedef struct _ship {
	int x;
	int y;
	int health;
	int current_sprite; /* gives the sprite index depending on the pressed key */
	int speed; /* speed vector */
	int has_missile; /* missle upgrade */
	int has_double; /* double shot upgrade */
	int has_laser; /* laser upgrade */
	int has_option; /* option upgrade */
	int invulnerability_frames; /* if hit by an enemy, invulnerable for some frames */
	/*
	Tir* projectiles; */ /* ship's projectiles */
}Ship;

/* --------------------------- */
void init_ship(Ship* ship)
/* --------------------------- */
{
	ship->x = WINDOW_WIDTH / 20;
	ship->y = (WINDOW_HEIGHT / 2) /*- (SPRITE_SIZE / 2)*/; /* in the middle of the screen */

	ship->health = 100;
	ship->current_sprite = IDLE;
	ship->speed = 1; /* added to the ship's position to make it move */

	ship->has_missile = 0;
	ship->has_double = 0;
	ship->has_laser = 0;
	ship->has_option = 0;

	ship->invulnerability_frames = 0;
/*
	projectiles = (Tir *)malloc(sizeof(Tir) * 100);
*/
}

/* --------------------------- */
void move_ship(Ship* ship, int move_x, int move_y)
/* --------------------------- */
{
	if((move_x && ship->x == WINDOW_WIDTH) || (move_x < 0 && ship->x == 0))
		return;
	if((move_y && ship->y == WINDOW_HEIGHT) || (move_y < 0 && ship->y == 0))
		return;

	ship->x += ship->speed * move_x;
	ship->y += ship->speed * move_y;
}


int main(int argc, char const *argv[])
{
	Ship gradius;

	init_ship(&gradius);

	printf("----------------------------------\n");
	printf("|Ship %s created            |\n", "gradius");
	printf("|--------------------------------|\n");
	printf("|      x      | %4d             |\n", gradius.x);
	printf("|      y      | %4d             |\n", gradius.y);
	printf("| HP          | %4d             |\n", gradius.health);
	printf("| CUR_SPRITE  | %4d             |\n", gradius.current_sprite);
	printf("| SPEED       | %4d             |\n", gradius.speed);
	printf("| has_missile | %4d             |\n", gradius.has_missile);
	printf("| has_double  | %4d             |\n", gradius.has_double);
	printf("| has_laser   | %4d             |\n", gradius.has_laser);
	printf("| has_option  | %4d             |\n", gradius.has_option);
	printf("| inv_frames  | %4d             |\n", gradius.has_option);

	printf("\n test moving ship...\n");
	printf("moving to the right\n");
	printf("x = %d ->", gradius.x);
	move_ship(&gradius, 1, 0);
	printf(" x = %d\n", gradius.x);

	printf("changing ship coordinates to bottom right border to test borders\n");
	gradius.x = WINDOW_WIDTH;
	gradius.y = WINDOW_HEIGHT;
	printf("(x,y) = (%d,%d) -> ", gradius.x, gradius.y);
	move_ship(&gradius, 1, 1);
	printf("(x,y) = (%d,%d)\n", gradius.x, gradius.y);

	return 0;
}