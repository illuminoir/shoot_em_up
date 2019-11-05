PROJET README


amélioration-
- déplacer le vaisseau avec zqsd/wasd if qwerty (chercher si possibilité différents contrôles, sinon un menu pour les changer ?)
-------------

- en plus de ^ viser avec la souris ?
		-> MLV_get_mouse_position(int* x, int* y);
				x 	Coordonnée en x de la souris
				y 	Coordonnée en y de la souris
		-> MLV_wait_mouse(int* x, int *y);           (pour le menu/cliquer sur des boutons/aller au niveau suivant);
				x 	Coordonnée en x de la souris
				y 	Coordonnée en y de la souris
		-> MLV_get_mouse_button_state(MLV_mouse_button mouse_button);    (pour voir si tire ou pas)
				mouse_button 	Code bouton souris
