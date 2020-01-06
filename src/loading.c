#include "../include/loading.h"

/* sounds */
MLV_Music* music;
MLV_Sound* enemy_hit; 
MLV_Sound* enemy_death;
MLV_Sound* ship_shoot_sound;

/* sprites for the ship */
MLV_Image* ship_idle;
MLV_Image* ship_moving_up;
MLV_Image* ship_moving_down;

/* sprites for the projectiles for the ship */
MLV_Image* ship_projectile;
MLV_Image* ship_laser;
MLV_Image* ship_missile;

/* sprites for the ship's option */
MLV_Image* ship_option_1;
MLV_Image* ship_option_2;

/* sprites for patterned enemies */
MLV_Image* patterned_sprite_idle;
MLV_Image* patterned_sprite_up;
MLV_Image* patterned_sprite_down;

/* sprites for lone projectile enemies */
MLV_Image* lone_projectile_first;
MLV_Image* lone_projectile_second;

/* sprites for cannon enemies */
MLV_Image* cannon_idle;
MLV_Image* cannon_angle_1;
MLV_Image* cannon_angle_2;
MLV_Image* cannon_projectile;

/* sprites for spinning enemies */
MLV_Image* spinning_sprite_1;
MLV_Image* spinning_sprite_2;
MLV_Image* spinning_sprite_3;
MLV_Image* spinning_sprite_4;

/* sprites for options */
MLV_Image* option1;
MLV_Image* option2;
MLV_Image* option3;
MLV_Image* option4;
MLV_Image* option5;
MLV_Image* option6;

/* sprites for selected options */
MLV_Image* option1_selected;
MLV_Image* option2_selected;
MLV_Image* option3_selected;
MLV_Image* option4_selected;
MLV_Image* option5_selected;

/* sprites for the bonuses */
MLV_Image* bonus1;
MLV_Image* bonus2;

/* ------------ */
void load_sounds()
/* ------------ */
{
	ship_shoot_sound = MLV_load_sound("audio/shooting_sound.ogg");
	music = MLV_load_music("audio/music.mp3");
	enemy_hit = MLV_load_sound("audio/enemy_hit_sound.ogg");
	enemy_death = MLV_load_sound("audio/enemy_death_sound.ogg");
}

/* --------------------- */
void load_sprites_enemies()
/* --------------------- */
{
	patterned_sprite_idle = MLV_load_image("img/enemies/patterned/enemy_sprite_1.png");
	patterned_sprite_up = MLV_load_image("img/enemies/patterned/enemy_sprite_2.png");
	patterned_sprite_down = MLV_load_image("img/enemies/patterned/enemy_sprite_3.png");

	lone_projectile_first = MLV_load_image("img/enemies/lone_shot/enemy_lone_shot_1.png");
	lone_projectile_second = MLV_load_image("img/enemies/lone_shot/enemy_lone_shot_2.png");

	cannon_idle = MLV_load_image("img/enemies/cannon/cannon_sprite_1.png");
	cannon_angle_1 = MLV_load_image("img/enemies/cannon/cannon_sprite_2.png");
	cannon_angle_2 = MLV_load_image("img/enemies/cannon/cannon_sprite_3.png");
	cannon_projectile = MLV_load_image("img/enemies/cannon/cannon_projectile.png");

	spinning_sprite_1 = MLV_load_image("img/enemies/spinning_enemy/spinning_enemy_sprite_1.png");
	spinning_sprite_2 = MLV_load_image("img/enemies/spinning_enemy/spinning_enemy_sprite_2.png");
	spinning_sprite_3 = MLV_load_image("img/enemies/spinning_enemy/spinning_enemy_sprite_3.png");
	spinning_sprite_4 = MLV_load_image("img/enemies/spinning_enemy/spinning_enemy_sprite_4.png");
}

/* ----------------------- */
void resize_sprites_enemies()
/* ----------------------- */
{
	MLV_resize_image_with_proportions(patterned_sprite_idle, PATTERNED_SIZE, PATTERNED_SIZE);
	MLV_resize_image_with_proportions(patterned_sprite_up, PATTERNED_SIZE, PATTERNED_SIZE);
	MLV_resize_image_with_proportions(patterned_sprite_down, PATTERNED_SIZE, PATTERNED_SIZE);

	MLV_resize_image_with_proportions(lone_projectile_first, LONE_PROJECTILE_SIZE, LONE_PROJECTILE_SIZE);
	MLV_resize_image_with_proportions(lone_projectile_second, LONE_PROJECTILE_SIZE, LONE_PROJECTILE_SIZE);

	MLV_resize_image_with_proportions(cannon_idle, CANNON_SIZE, CANNON_SIZE);
	MLV_resize_image_with_proportions(cannon_angle_1, CANNON_SIZE, CANNON_SIZE);
	MLV_resize_image_with_proportions(cannon_angle_2, CANNON_SIZE, CANNON_SIZE);
	MLV_resize_image_with_proportions(cannon_projectile, PROJECTILE_SIZE, PROJECTILE_SIZE);

	MLV_resize_image_with_proportions(spinning_sprite_1, SPINNING_SIZE, SPINNING_SIZE);
	MLV_resize_image_with_proportions(spinning_sprite_2, SPINNING_SIZE, SPINNING_SIZE);
	MLV_resize_image_with_proportions(spinning_sprite_3, SPINNING_SIZE, SPINNING_SIZE);
	MLV_resize_image_with_proportions(spinning_sprite_4, SPINNING_SIZE, SPINNING_SIZE);
}

/* ------------- */
void load_options()
/* ------------- */
{
	option1 = MLV_load_image("img/options/option_1.png");
	option2 = MLV_load_image("img/options/option_2.png");
	option3 = MLV_load_image("img/options/option_3.png");
	option4 = MLV_load_image("img/options/option_4.png");
	option5 = MLV_load_image("img/options/option_5.png");
	option6 = MLV_load_image("img/options/option_6.png");
}

/* --------------- */
void resize_options()
/* --------------- */
{
	MLV_resize_image_with_proportions(option1, IMG_OPT_SIZE_X, IMG_OPT_SIZE_Y);
	MLV_resize_image_with_proportions(option2, IMG_OPT_SIZE_X, IMG_OPT_SIZE_Y);
	MLV_resize_image_with_proportions(option3, IMG_OPT_SIZE_X, IMG_OPT_SIZE_Y);
	MLV_resize_image_with_proportions(option4, IMG_OPT_SIZE_X, IMG_OPT_SIZE_Y);
	MLV_resize_image_with_proportions(option5, IMG_OPT_SIZE_X, IMG_OPT_SIZE_Y);
	MLV_resize_image_with_proportions(option6, IMG_OPT_SIZE_X, IMG_OPT_SIZE_Y);
}

/* ---------------------- */
void load_selected_options()
/* ---------------------- */
{
	option1_selected = MLV_load_image("img/options/option_1_selected.png");
	option2_selected = MLV_load_image("img/options/option_2_selected.png");
	option3_selected = MLV_load_image("img/options/option_3_selected.png");
	option4_selected = MLV_load_image("img/options/option_4_selected.png");
	option5_selected = MLV_load_image("img/options/option_5_selected.png");
}

/* ------------------------ */
void resize_selected_options()
/* ------------------------ */
{
	MLV_resize_image_with_proportions(option1_selected, IMG_OPT_SIZE_X, IMG_OPT_SIZE_Y);
	MLV_resize_image_with_proportions(option2_selected, IMG_OPT_SIZE_X, IMG_OPT_SIZE_Y);
	MLV_resize_image_with_proportions(option3_selected, IMG_OPT_SIZE_X, IMG_OPT_SIZE_Y);
	MLV_resize_image_with_proportions(option4_selected, IMG_OPT_SIZE_X, IMG_OPT_SIZE_Y);
	MLV_resize_image_with_proportions(option5_selected, IMG_OPT_SIZE_X, IMG_OPT_SIZE_Y);
}

/* ------------------ */
void load_sprites_ship()
/* ------------------ */
{
	ship_idle = MLV_load_image("img/ship/ship_idle.png");
	ship_moving_up = MLV_load_image("img/ship/ship_moving_up.png");
	ship_moving_down = MLV_load_image("img/ship/ship_moving_down.png");

	ship_projectile = MLV_load_image("img/ship/projectile_ship.png");
	ship_laser = MLV_load_image("img/ship/laser_ship.png");
	ship_missile = MLV_load_image("img/ship/missile_ship_falling.png");
}

/* -------------------- */
void resize_sprites_ship()
/* -------------------- */
{
	MLV_resize_image_with_proportions(ship_idle, SHIP_SIZE, SHIP_SIZE);
	MLV_resize_image_with_proportions(ship_moving_up, SHIP_SIZE, SHIP_SIZE);
	MLV_resize_image_with_proportions(ship_moving_down, SHIP_SIZE, SHIP_SIZE);

	MLV_resize_image_with_proportions(ship_projectile, PROJECTILE_SIZE, PROJECTILE_SIZE);
	MLV_resize_image_with_proportions(ship_laser, PROJECTILE_SIZE, PROJECTILE_SIZE);
	MLV_resize_image_with_proportions(ship_missile, PROJECTILE_SIZE, PROJECTILE_SIZE);
}

/* ------------------------- */
void load_sprites_ship_option()
/* ------------------------- */
{
	ship_option_1 = MLV_load_image("img/ship/option_1.png");
	ship_option_2 = MLV_load_image("img/ship/option_2.png");
}

/* --------------------------- */
void resize_sprites_ship_option()
/* --------------------------- */
{
	MLV_resize_image_with_proportions(ship_option_1, SHIP_OPT_SIZE, SHIP_OPT_SIZE);
	MLV_resize_image_with_proportions(ship_option_2, SHIP_OPT_SIZE, SHIP_OPT_SIZE);
}

/* ------------- */
void load_bonuses()
/* ------------- */
{
	bonus1 = MLV_load_image("img/item_loot_1_1.png");
	bonus2 = MLV_load_image("img/item_loot_1_2.png");
}

/* --------------- */
void resize_bonuses()
/* --------------- */
{
	MLV_resize_image_with_proportions(bonus1, BONUS_SIZE, BONUS_SIZE);
	MLV_resize_image_with_proportions(bonus2, BONUS_SIZE, BONUS_SIZE);
}

/* -------------- */
void load_all_data()
/* -------------- */
{
	load_sounds();
	load_options();
	load_selected_options();
	load_sprites_enemies();
	load_sprites_ship();
	load_sprites_ship_option();
	load_bonuses();
	resize_options();
	resize_selected_options();
	resize_sprites_enemies();
	resize_sprites_ship();
	resize_sprites_ship_option();
	resize_bonuses();
}

/* ---------------- */
void free_everything()
/* ---------------- */
{
	MLV_free_image(ship_idle);
	MLV_free_image(ship_moving_up);
	MLV_free_image(ship_moving_down);
	MLV_free_image(ship_projectile);
	MLV_free_image(ship_laser);
	MLV_free_image(ship_missile);
	MLV_free_image(ship_option_1);
	MLV_free_image(ship_option_2);
	MLV_free_image(patterned_sprite_idle);
	MLV_free_image(patterned_sprite_up);
	MLV_free_image(patterned_sprite_down);
	MLV_free_image(lone_projectile_first);
	MLV_free_image(lone_projectile_second);
	MLV_free_image(cannon_idle);
	MLV_free_image(cannon_angle_1);
	MLV_free_image(cannon_angle_2);
	MLV_free_image(spinning_sprite_1);
	MLV_free_image(spinning_sprite_2);
	MLV_free_image(spinning_sprite_3);
	MLV_free_image(spinning_sprite_4);
	MLV_free_image(option1);
	MLV_free_image(option2);
	MLV_free_image(option3);
	MLV_free_image(option4);
	MLV_free_image(option5);
	MLV_free_image(option6);
	MLV_free_image(option1_selected);
	MLV_free_image(option2_selected);
	MLV_free_image(option3_selected);
	MLV_free_image(option4_selected);
	MLV_free_image(option5_selected);
	MLV_free_image(bonus1);
	MLV_free_image(bonus2);

	MLV_free_music(music);
	MLV_free_sound(enemy_hit);
	MLV_free_sound(enemy_death);
	MLV_free_sound(ship_shoot_sound);
}