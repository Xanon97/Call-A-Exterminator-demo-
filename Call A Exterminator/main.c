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
	SDL_Rect src, dst;
}ground;

//surface and texture pointers
SDL_Surface* image;
SDL_Surface* image2;
SDL_Surface* image3;
SDL_Surface* image4;
SDL_Surface* image5;

SDL_Texture* texture;
SDL_Texture* interior_textures;
SDL_Texture* door_texture;
SDL_Texture* background_tex;

//collision box
SDL_Rect collide_box = {500, 400, 200, 200};




//level loader
void load_level(int current_level)
{

	//walls & roof
	texture = SDL_CreateTextureFromSurface(renderer,image3);
	door_texture = SDL_CreateTextureFromSurface(renderer,image2);

	interior_textures = SDL_CreateTextureFromSurface(renderer,image4);

	//background photo
	background_tex = SDL_CreateTextureFromSurface(renderer,image5);

	switch(current_level)
	{
		case 0:	

			for(int i = 0;i<map_width;i++)
			{
				for(int j = 0;j<map_height;j++)
				{
				if(level_0[i][j] == _ground_)
				{
					SDL_Rect grass = {j * tile_size, i * tile_size, tile_size, tile_size};
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					SDL_RenderFillRect(renderer, &grass);
				}
				if(level_0[j][i] == Wall)
				{
					wall.src.x = 304;
					wall.src.y = 2;
					wall.src.w = 100;
					wall.src.h = 100;
					wall.dst.x = i * tile_size;
					wall.dst.y = j * tile_size;
					wall.dst.w = tile_size;
					wall.dst.h = tile_size;
					SDL_RenderCopy(renderer, texture, &wall.src, &wall.dst);
				}
				if(level_0[j][i] == Roof)
				{
					roof.src.x = 0;
					roof.src.y = 0;
					roof.src.w = 100;
					roof.src.h = 100;
					roof.dst.x = i * tile_size;
					roof.dst.y = j * tile_size;
					roof.dst.w = tile_size;
					roof.dst.h = tile_size;
					SDL_RenderCopy(renderer, texture, &roof.src, &roof.dst);
				}
				}
			}
			//door	
			door.src.x;
			door.src.y;
			door.src.w = 100;
			door.src.h = 200;
			door.dst.x = 400; 
			door.dst.y = 400; 
			door.dst.w = 100;
			door.dst.h = 200;
			//copy textures to door rect
			SDL_RenderCopy(renderer, door_texture, &door.src, &door.dst);
			SDL_SetRenderDrawColor(renderer, 127, 0, 255, 255);
			break;
		case 1:
			SDL_RenderCopy(renderer, background_tex, NULL, NULL);

			for(int i = 0;i<map_width;i++)
			{
				for(int j = 0;j<map_height;j++)
				{
				if(level_1[j][i] == _ground_)
				{
					ground.src.x = 100;
					ground.src.y = 0;
					ground.src.w = 100;
					ground.src.h = 100;
					ground.dst.x = i * tile_size;
					ground.dst.y = j * tile_size;
					ground.dst.w = tile_size;
					ground.dst.h = tile_size;
					SDL_RenderCopy(renderer, texture, &ground.src, &ground.dst);

				}
				if(level_1[j][i] == stairs)
				{
					SDL_Rect src, dst;

					src.x = 0;
					src.y = 0;
					src.w = 200;
					src.h = 200;
					dst.x = i * tile_size + -100;
					dst.y = j * tile_size + -100;
					dst.w = tile_size * 2;
					dst.h = tile_size * 2;
					SDL_RenderCopy(renderer, interior_textures, &src, &dst);

				}
				if(level_1[j][i] == painting)
				{
					SDL_Rect src, dst;

					src.x = 200;
					src.y = 200;
					src.w = 200;
					src.h = 200;
					dst.x = i * tile_size + -100;
					dst.y = j * tile_size + -100;
					dst.w = tile_size * 2;
					dst.h = tile_size * 2;
					SDL_RenderCopy(renderer, interior_textures, &src, &dst);

				}
				}
			}
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(renderer, &collide_box);
			break;
		case 2:
			for(int i = 0;i<map_width;i++)
			{
				for(int j = 0;j<map_height;j++)
				{
				if(level_2[j][i] == _ground_)
				{
					ground.src.x = 100;
					ground.src.y = 0;
					ground.src.w = 100;
					ground.src.h = 100;
					ground.dst.x = i * tile_size;
					ground.dst.y = j * tile_size;
					ground.dst.w = tile_size;
					ground.dst.h = tile_size;
					SDL_RenderCopy(renderer, texture, &ground.src, &ground.dst);
				}
				if(level_2[j][i] == Door)
				{
					door.dst.x = i * tile_size; 
					door.dst.y = j * tile_size; 
					door.dst.w = 100;
					door.dst.h = 200;
					SDL_RenderCopy(renderer, door_texture, NULL, &door.dst);

				}
				if(level_2[j][i] == glass_window)
				{	SDL_Rect src, dst;
					
					src.x = 0;
					src.y = 400;
					src.w = 200;
					src.h = 200;
					dst.x = i * tile_size;
					dst.y = j * tile_size;
					dst.w = tile_size;
					dst.h = tile_size;
					SDL_RenderCopy(renderer, interior_textures, &src, &dst);
				}
				if(level_2[j][i] == painting)
				{	SDL_Rect src, dst;
					
					src.x = 600;
					src.y = 200;
					src.w = 200;
					src.h = 200;
					dst.x = i * tile_size - 50;
					dst.y = j * tile_size;
					dst.w = tile_size;
					dst.h = tile_size;
					SDL_RenderCopy(renderer, interior_textures, &src, &dst);
				}
				}
			}

			SDL_SetRenderDrawColor(renderer, 0, 255, 180, 255);
			break;
		default:
			printf("out of range level\n");
	}
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
}

//check for rectangle collisions
bool collideRect()
{	
	if(current_level < 1 && SDL_HasIntersection(&player.dst, &door.dst))
	{
		printf("Collision with target detected!\n");
		printf("initializing next level\n");
		current_level += 1;
		player.dst.x = 0;
		return true;
	}
	if(current_level < 2 && SDL_HasIntersection(&player.dst, &collide_box))
	{
		printf("Collision with target detected!\n");
		printf("initializing next level\n");
		current_level += 1;
		player.dst.x = 0;
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
	SDL_RenderClear(renderer);
}

int main(int args, char** argv){
	Window();		
	//Create_Textures();
	image5 = IMG_Load("assets/background2.jpg");
	image4 = IMG_Load("assets/interior_sprites.png");	
	image3 = IMG_Load("assets/house_texture.png");
	image2 = IMG_Load("assets/door.png");
	image = IMG_Load("assets/charRight_spritesheet.png");	

	//initialize SDL2 and SDL_image
	SDL_Init(SDL_INIT_VIDEO);
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL failed to initialize\n",SDL_GetError());
		exit(1);
	}
	IMG_Init(IMG_INIT_PNG && IMG_INIT_JPG);
	if(IMG_Init(IMG_INIT_PNG)<0){
		printf("SDL_image failed to initialize\n",SDL_GetError());
		exit(1);
	}

	bool quit = false;
	while(!quit){
		//clear frames
		clear();
		//clear print output
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
	SDL_FreeSurface(image);SDL_FreeSurface(image2);SDL_FreeSurface(image3);SDL_FreeSurface(image4);SDL_FreeSurface(image5);

	SDL_DestroyTexture(texture);SDL_DestroyTexture(door_texture);SDL_DestroyTexture(interior_textures);SDL_DestroyTexture(background_tex);

	//end of game loop
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
