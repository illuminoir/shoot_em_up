#include <stdio.h>
#include <MLV/MLV_all.h>

int main(int argc, char const *argv[])
{
	unsigned int width, height;
	int img_w, img_h;
	MLV_Image* ship, *projectile1, *projectile2, *projectile3;

	MLV_get_desktop_size(&width, &height);

	MLV_create_window("yes", "yes", width, height);

	ship = MLV_load_image("../img/ship_idle.png");
	MLV_resize_image_with_proportions(ship, height / 10, height / 10);

	projectile1 = MLV_load_image("../img/projectile_ship.png");
	MLV_get_image_size(projectile1, &img_w, &img_h);
	projectile2 = MLV_load_image("../img/projectile_ship.png");
	projectile3 = MLV_load_image("../img/projectile_ship.png");
	MLV_resize_image_with_proportions(projectile1, img_w * 3, img_h * 3);
	MLV_resize_image_with_proportions(projectile2, img_w * 3, img_h * 3);
	MLV_resize_image_with_proportions(projectile3, img_w * 3, img_h * 3);

	MLV_draw_image(ship, width / 2, height / 2);

	MLV_draw_image(projectile1, width / 2 + (height / 10) + 10, height / 2 + (height / 25));
	MLV_draw_image(projectile2, width / 2 + (height / 10) + 40, height / 2 + (height / 25));
	MLV_draw_image(projectile3, width / 2 + (height / 10) + 70, height / 2 + (height / 25));

	MLV_actualise_window();

	MLV_wait_mouse(NULL, NULL);


	return 0;
}