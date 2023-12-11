#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "level_map.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define Width 700
#define Height 700

SDL_Window * window;
SDL_Renderer * renderer;
SDL_Event event;

//player variable struct
struct Player
{
	SDL_Rect src, dst;
}player;

//level_0 object variable struct
struct level_0
{
	SDL_Rect src, dst;

}door,wall,roof;

struct floor{
	int x;
	int y;
	int w;
	int h;
}grnd;

//surface and texture pointers
SDL_Surface* image;
SDL_Surface* image2;
SDL_Surface* image3;
SDL_Texture* texture;



//level loader
void load_level(int current_level)
{

	switch(current_level)
	{
		case 0:
			draw_world();
			break;
		case 1:
			for(int i = 0;i<map_width;i++)
			{
				for(int j = 0;j<map_height;j++)
				{
				if(level[i][j] == block)
				{
					SDL_Rect test_Block = {j * tile_size, i * tile_size, tile_size, tile_size};
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					SDL_RenderFillRect(renderer, &test_Block);
				}
				}
			}
			break;		
		case 2:
			for(int i = 0;i<map_width;i++)
			{
				for(int j = 0;j<map_height;j++)
				{
				if(level[i][j] == block)
				{
					SDL_Rect test_Block = {j * tile_size, i * tile_size, tile_size, tile_size};
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
					SDL_RenderFillRect(renderer, &test_Block);
				}
				}
			}
			break;
		default:
			printf("level is not available\n");
	}
}

void draw_world(){
	//grass
	SDL_Rect grass = {grnd.x, grnd.y = Height - 100, grnd.w = Width, grnd.h = 100};
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &grass);
	//walls & roof
	texture = SDL_CreateTextureFromSurface(renderer,image3);
	for(int wall_row1 = 0;wall_row1<3;wall_row1++)
	{	
		wall.src.x = 304;
		wall.src.y = 2;
		wall.src.w = 100;
		wall.src.h = 100;
		
		wall.dst.x = door.dst.x + wall_row1 * 100;
		wall.dst.y = door.dst.y-100;
		wall.dst.w = 100;
		wall.dst.h = 100;
		SDL_RenderCopy(renderer, texture, &wall.src, &wall.dst);
		for(int wall_row2 = 0;wall_row2<2;wall_row2++)
		{
			wall.dst.x = 100 + door.dst.x + wall_row2 * 100;
			wall.dst.y = door.dst.y;
			wall.dst.w = 100;
			wall.dst.h = 100;
			SDL_RenderCopy(renderer, texture, &wall.src, &wall.dst);

		}
		for(int wall_row3 = 0;wall_row3<2;wall_row3++)
		{
			wall.dst.x = 100 + door.dst.x + wall_row3 * 100;
			wall.dst.y = door.dst.y + 100;
			wall.dst.w = 100;
			wall.dst.h = 100;
			SDL_RenderCopy(renderer, texture, &wall.src, &wall.dst);

		}
		//draws roof of house
		for(int roof_row1 = 0;roof_row1 < 4;roof_row1++)
		{			
		roof.src.x = 0;
		roof.src.y = 0;
		roof.src.w = 100;
		roof.src.h = 100;

		roof.dst.x = door.dst.x - 100 + roof_row1 * 100;
		roof.dst.y = door.dst.y-200;
		roof.dst.w = 100;
		roof.dst.h = 100;
		SDL_RenderCopy(renderer, texture, &roof.src, &roof.dst);
		}
		for(int roof_row2 = 0;roof_row2 < 3;roof_row2++)
		{			
		roof.src.x = 0;
		roof.src.y = 0;
		roof.src.w = 100;
		roof.src.h = 100;

		roof.dst.x = door.dst.x + roof_row2 * 100;
		roof.dst.y = door.dst.y - 300;
		roof.dst.w = 100;
		roof.dst.h = 100;
		SDL_RenderCopy(renderer, texture, &roof.src, &roof.dst);
		}
		for(int roof_row2 = 0;roof_row2 < 2;roof_row2++)
		{			
		roof.src.x = 0;
		roof.src.y = 0;
		roof.src.w = 100;
		roof.src.h = 100;

		roof.dst.x = 100 + door.dst.x + roof_row2 * 100;
		roof.dst.y = door.dst.y - 400;
		roof.dst.w = 100;
		roof.dst.h = 100;
		SDL_RenderCopy(renderer, texture, &roof.src, &roof.dst);
		}




	}
	//door	
	texture = SDL_CreateTextureFromSurface(renderer,image2);
	door.src.x;
	door.src.y;
	door.src.w = 100;
	door.src.h = 200;
	
	door.dst.x = 450; 
	door.dst.y = 400; 
	door.dst.w = 100; 
	door.dst.h = 200;

	//copy textures to rects
	SDL_RenderCopy(renderer, texture, &door.src, &door.dst);
}
//create player tiles
void draw_player(){
	//character tiles
	texture = SDL_CreateTextureFromSurface(renderer,image);
	player.src.x;
	player.src.y;
	player.src.w = 100;
	player.src.h = 100;

	player.dst.x; 
	player.dst.y;
	player.dst.w = 100; 
	player.dst.h = 100;
	
	//copy textures of player sprite to rectangle
	SDL_RenderCopy(renderer, texture, &player.src, &player.dst);	
	//find a way to seperate rendering and updating player position/size in the future
}

//create a window
void Window(){
	window = SDL_CreateWindow("Call A Exterminator",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,Width,Height,0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 127, 0, 255, 255);
}

//check for rectangle collisions
bool collideRect()
{


	bool collide = SDL_HasIntersection(&player.dst, &door.dst);

	if(collide)
	{
		printf("player is touching door\n");
		current_level = 1;
		return true;
	}
}

void gravity(){
	int g_force = 10;
	if(player.dst.y  + player.dst.h <= 591){
		player.dst.y += g_force;
	}
}

void clear(){
	SDL_SetRenderDrawColor(renderer, 127, 0, 255, 255);
	SDL_RenderClear(renderer);
}

int main(int args, char** argv){
	Window();		
	//Create_Textures();
	image3 = IMG_Load("assets/house_texture.png");
	image2 = IMG_Load("assets/door.png");
	image = IMG_Load("assets/charRight_spritesheet.png");	

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
		//clear frames
		clear();
		//clear print output
		system("clear");
		collideRect();
		//gravity
		gravity();
		//draws player and world sprites
		load_level(current_level);
		draw_player();
		//shows image on screen
		SDL_RenderPresent(renderer);
		while(SDL_PollEvent(&event)!=0){
		//printf("x = %d y = %d rx = %d ry = %d\n",player.x,player.y,rx,ry);

			//controls
			if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym)
				{
				case SDLK_a: 
					player.src.y = 100;
					player.dst.x -= 10;
					player.src.x -= 100;	
					break;
				case SDLK_d:
					player.src.y = 0;
					player.dst.x += 10;
					player.src.x += 100;
					break;
				}
			}	
			
			//corrects position of destination square coordinates
			if(player.src.x > 100)
				player.src.x = 0;	
			if(player.src.x < 0)
				player.src.x = 100;
			//checks screen boundary
			if(player.dst.x < 0)
				player.dst.x += 10;
			if(player.dst.x > Width - 100)
				player.dst.x -= 10;

			//exits game
			if(event.type == SDL_QUIT)
				quit = true;
		}
	}
	
	//clean up
	SDL_FreeSurface(image);SDL_FreeSurface(image2);SDL_FreeSurface(image3);
	SDL_DestroyTexture(texture);

	//end of game loop
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
