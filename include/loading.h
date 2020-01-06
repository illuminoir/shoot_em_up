#ifndef __LOADING__
#define __LOADING__

#include <MLV/MLV_all.h>

extern MLV_Music* music;
extern MLV_Sound* enemy_hit; 
extern MLV_Sound* enemy_death;
extern MLV_Sound* ship_shoot_sound;

extern MLV_Image* ship_idle;
extern MLV_Image* ship_moving_up;
extern MLV_Image* ship_moving_down;

extern MLV_Image* ship_projectile;
extern MLV_Image* ship_laser;
extern MLV_Image* ship_missile;

extern MLV_Image* ship_option_1;
extern MLV_Image* ship_option_2;

extern MLV_Image* patterned_sprite_idle;
extern MLV_Image* patterned_sprite_up;
extern MLV_Image* patterned_sprite_down;

extern MLV_Image* lone_projectile_first;
extern MLV_Image* lone_projectile_second;

extern MLV_Image* cannon_idle;
extern MLV_Image* cannon_angle_1;
extern MLV_Image* cannon_angle_2;
extern MLV_Image* cannon_projectile;

extern MLV_Image* spinning_sprite_1;
extern MLV_Image* spinning_sprite_2;
extern MLV_Image* spinning_sprite_3;
extern MLV_Image* spinning_sprite_4;

extern MLV_Image* option1;
extern MLV_Image* option2;
extern MLV_Image* option3;
extern MLV_Image* option4;
extern MLV_Image* option5;
extern MLV_Image* option6;

extern MLV_Image* option1_selected;
extern MLV_Image* option2_selected;
extern MLV_Image* option3_selected;
extern MLV_Image* option4_selected;
extern MLV_Image* option5_selected;

extern MLV_Image* bonus1;
extern MLV_Image* bonus2;

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define CANNON_SIZE 60
#define LONE_PROJECTILE_SIZE 60
#define PATTERNED_SIZE 60
#define SPINNING_SIZE 60

#define BONUS_SIZE 40

#define SHOT_FRAMES_WAIT 60
#define MISSILES_FRAMES_WAIT 90

#define IMG_OPT_SIZE_X WINDOW_WIDTH / 12 - 5
#define IMG_OPT_SIZE_Y WINDOW_HEIGHT / 20 

#define SHIP_SIZE WINDOW_WIDTH / 15
#define PROJECTILE_SIZE WINDOW_WIDTH / 80

#define SHIP_OPT_SIZE 50

/* load the sounds and music for the game */
void load_sounds();

/* load the sprites for the enemies */
void load_sprites_enemies();

/* resize the sprites for the enemies */
void resize_sprites_enemies();

/* load the sprites for the options */
void load_options();

/* resize the sprites for the options */
void resize_options();

/* load the sprites for the options when selected */
void load_selected_options();

/* resize the sprites for the options when selected */
void resize_selected_options();

/* load the sprites for the ship */
void load_sprites_ship();

/* resize the sprites for the ship */
void resize_sprites_ship();

/* load the sprites for the option object for the ship */
void load_sprites_ship_option();

/* resize the sprites for the option object for the ship */
void resize_sprites_ship_option();

/* load the sprites for the bonus object */
void load_bonuses();

/* resize the sprites for the bonus object */
void resize_bonuses();

/* load all data, calls all the previous functions */
void load_all_data();

/* frees all the data previously loaded */
void free_everything();

#endif