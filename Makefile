# Makefile gradius C

# $@ : the current target
# $< : the current prerequisites
# $< : the first current prerequisite

CC=gcc
CFLAGS=-Wall -ansi -pedantic -g

gradius: bin/main.o bin/projectiles.o bin/ship.o bin/enemy.o bin/collisions.o bin/display_ship.o bin/display_enemies.o bin/display_game.o bin/game.o
	$(CC) -o $@ $^ $(CFLAGS) -lMLV

bin/projectiles.o: src/projectiles.c include/projectiles.h
	$(CC) -o $@ $< $(CFLAGS) -c

bin/ship.o: src/ship.c include/ship.h include/projectiles.h
	$(CC) -o $@ $< $(CFLAGS) -c

bin/enemy.o: src/enemy.c include/enemy.h include/projectiles.h
	$(CC) -o $@ $< $(CFLAGS) -c

bin/collisions.o: src/collisions.c include/collisions.h include/ship.h include/enemy.h
	$(CC) -o $@ $< $(CFLAGS) -c

bin/display_ship.o: src/display_ship.c include/display_ship.h include/ship.h
	$(CC) -o $@ $< $(CFLAGS) -c -lMLV

bin/display_enemies.o: src/display_enemies.c include/display_enemies.h include/enemy.h
	$(CC) -o $@ $< $(CFLAGS) -c -lMLV

bin/display_game.o: src/display_game.c include/display_game.h include/display_ship.h include/display_enemies.h
	$(CC) -o $@ $< $(CFLAGS) -c -lMLV

bin/game.o: src/game.c include/game.h include/display_game.h include/collisions.h
	$(CC) -o $@ $< $(CFLAGS) -c -lMLV -D_POSIX_C_SOURCE=199309L

bin/main.o: src/main.c include/game.h
	$(CC) -o $@ $< $(CFLAGS) -c



clean:
	rm gradius
	rm bin/*