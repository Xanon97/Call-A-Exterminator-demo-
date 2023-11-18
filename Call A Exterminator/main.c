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

//player variable struct
struct char_struct{
	int x;
	int y; 
	int w; 
	int h;
}player;

//level_0 object variable struct
struct lvl_0{
	int x;
	int y;
	int w;
	int h;
}door,grnd;

//source rect coordinates
int rx, ry;
int rx2, ry2;
int rx3, ry3;

void draw_world(){
	//grass
	SDL_Rect grass = {grnd.x, grnd.y = Height - 100, grnd.w = Width, grnd.h = 100};
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &grass);
	//walls & roof
	SDL_Surface* image3;
	image3 = IMG_Load("assets/house_texture.png");
	SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer,image3);
	SDL_Rect wall_sprt = {rx3 = 102,ry3 = 2,100,100};
	SDL_Rect wall;

	for(int i;i<4;i++)
	{
		wall.w = 100;
		wall.h = 100;
		wall.x = i * 100;
		wall.y = i *100 + 200;
		
	}
	//door
	SDL_Surface* image2;
	image2 = IMG_Load("assets/door.png");
	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer,image2);
	SDL_Rect srcrect2 = {rx2,ry2,100,200};
	SDL_Rect dstrect2 = {door.x = 450, door.y = 400, door.w = 100, door.h = 200};

	//copy textures to rects
	SDL_RenderCopy(renderer, texture3, &wall_sprt, &wall);
	SDL_RenderCopy(renderer, texture2, &srcrect2, &dstrect2);
}

//create player tiles
void draw_player(){
	//character tiles
	SDL_Surface* image;
	image = IMG_Load("assets/charRight_spritesheet.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,image);
	SDL_Rect srcrect = {rx,ry,100,100};
	SDL_Rect dstrect = {player.x, player.y, player.w = 100, player.h = 100};
	//copy textures of player sprite to rectangle
	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
	//free image from memory
	SDL_FreeSurface(image);
}

//create a window
void Window(){
	window = SDL_CreateWindow("Call A Exterminator",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,Width,Height,0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 127, 0, 255, 255);
}
void gravity(){
	int g_force = 10;
	if(player.x>=grnd.w||player.y<=490){
		player.y += g_force;
	}
}

void clear(){
	SDL_SetRenderDrawColor(renderer, 127, 0, 255, 255);
	SDL_RenderClear(renderer);
}

int main(int args, char** argv){
	Window();
	//initialize SDL2 and SDL_image
	SDL_Init(SDL_INIT_VIDEO);
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL failed to initialize\n",SDL_GetError());
		exit(1);
	}
	IMG_Init(IMG_INIT_PNG);
	if(IMG_Init(IMG_INIT_PNG)<0){
		printf("SDL_image failed to initialize\n",SDL_GetError());
		exit(1);
	}

	bool quit = false;
	while(!quit){
		//gravity
		gravity();
		//clears previous rendered objects from screen
		clear();
		//player and world sprites
		draw_world();
		draw_player();
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
			
			//corrects position of destination square coordinates
			if(rx > 100)
				rx = 0;	
			if(rx < 0)
				rx = 100;
			//checks screen boundary
			if(player.x < 0)
				player.x += 10;
			if(player.x > Width - 100)
				player.x -= 10;

			//exits game
			if(event.type == SDL_QUIT)
				quit = true;
		}
	//shows rendered objects
	SDL_RenderPresent(renderer);
	}

	//end of game loop
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
