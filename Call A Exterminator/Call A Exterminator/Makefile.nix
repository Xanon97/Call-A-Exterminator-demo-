main:
	gcc -o game main.c -lSDL2_image `sdl2-config --cflags --libs`
