#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define Width 700
#define Height 700

SDL_Window * window;
SDL_Renderer * renderer;
SDL_Event event;

struct dimensions {
	int x;
	int y; 
	int w; 
	int h;
}player;

struct level_attrib{
	int x;
	int y;
	int w;
	int h;
}lvl0;




int rx, ry;
	
//render tiles
void draw(){
	//grass
	SDL_Rect grass = {lvl0.x, lvl0.y = Height - 100, lvl0.w = Width, lvl0.h = 100};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &grass);

	//character tiles
	SDL_Surface* image;
	image = IMG_Load("assets/charRight_spritesheet.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,image);
	SDL_Rect srcrect = {rx,ry,100,100};
	SDL_Rect dstrect = {player.x, player.y, player.w = 100, player.h = 100};
	//render & show rectangles
	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
	SDL_RenderPresent(renderer);
	//free image from memory
	SDL_FreeSurface(image);
	SDL_DestroyTexture(texture);
}

//create a window
void Window(){
	window = SDL_CreateWindow("Call A Exterminator",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,Width,Height,0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 127, 0, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}
void clear(){
	SDL_SetRenderDrawColor(renderer, 127, 0, 255, 255);
	SDL_RenderClear(renderer);
}

//gravity
void gravity(){
	int ground = Height - 200;
	int g_force = 10;
	if(player.y!=ground){
		player.y += g_force;
	}
}

int main(int args, char** argv){
	Window();
	//initialize SDL2 and SDL_image
	SDL_Init(SDL_INIT_VIDEO);
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL failed to initialize\n");SDL_GetError();
		exit(1);
	}
	IMG_Init(IMG_INIT_PNG);
	if(IMG_Init(IMG_INIT_PNG)<0){
		printf("SDL_image failed to initialize\n");SDL_GetError();
		exit(1);
	}

	bool quit = false;
	while(!quit){
		//gravity
		gravity();
		clear();
		draw();
		while(SDL_PollEvent(&event)!=0){
			system("clear");
			printf("x = %d y = %d rx = %d ry = %d\n",player.x,player.y,rx,ry);

			//controls
			if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym)
				{
				case SDLK_a: 
					ry = 100;
					player.x -= 10;
					rx -= 100;	
					break;
				case SDLK_d:
					ry = 0;
					player.x += 10;
					rx += 100;
					break;
				}
			}	
			
			//corrects position of destination square cordinates
			if(rx > 100)
				rx = 0;	
			if(rx < 0)
				rx = 100;
			//checks wall collisions
			if(player.x < 0)
				player.x += 10;
			if(player.x > Width - 100)
				player.x -= 10;

			//exits game
			if(event.type == SDL_QUIT)
				quit = true;
		}
	}
	
	//end of game loop
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
