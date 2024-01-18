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
SDL_Texture* player_tex;
SDL_Texture* interior_textures;
SDL_Texture* door_texture;
SDL_Texture* background_tex;

//collision box
SDL_Rect collide_box = {500, 400, 200, 200};
SDL_Rect collide_box2;
SDL_Rect collide_box3;

struct particle_struct
{
	int x, y;
	int spread;
}particle[3];

bool spray = false;

int spray_pixels(int count)
{	
	const int xv = 1;
	const int yv = 1;
	if(count > 2)
	{
		return 1;
	}	
		
	if(spray == true)
	{
		particle[count].x = count + Width / 2;

		particle[0].x += particle[count].spread / 2;	
		particle[2].x -= particle[count].spread / 2;
		
		particle[count].spread += xv;
		particle[count].y += yv;
		
		SDL_RenderDrawPoint(renderer, particle[count].x, particle[count].y);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	
	
	}	
	
	return spray_pixels(count + 1);
}

//level loader
void load_level(int current_level)
{
	switch(current_level)
	{
		case 0:
			SDL_SetRenderDrawColor(renderer, 127, 0, 255, 255);
			SDL_RenderClear(renderer);
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
			SDL_SetRenderDrawColor(renderer, 0, 255, 180, 255);
			SDL_RenderClear(renderer);
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

					collide_box2.x = door.dst.x;
					collide_box2.y = door.dst.y;
					collide_box2.w = door.dst.w;
					collide_box2.h = door.dst.h;

					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					SDL_RenderDrawRect(renderer, &collide_box2);


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
			break;
		case 3:	
			SDL_SetRenderDrawColor(renderer, 245, 245, 220, 255);
			SDL_RenderClear(renderer);
			for(int i = 0;i<map_width;i++)
			{
				for(int j = 0;j<map_height;j++)
				{
					if(level_3[j][i] == '#')
					{
					ground.src.x = 0;
					ground.src.y = 0;
					ground.src.w = tile_size;
					ground.src.h = tile_size;
					ground.dst.x = i * tile_size;
					ground.dst.y = j * tile_size;
					ground.dst.w = tile_size;
					ground.dst.h = tile_size;
					SDL_RenderCopy(renderer, texture, &ground.src, &ground.dst);
					} 
					
					if(level_3[j][i] == 's')
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
					
					if(level_3[j][i] == 'c')
					{

					SDL_Rect src, dst;

					src.x = 0;
					src.y = 200;
					src.w = 200;
					src.h = 200;
					dst.x = i * tile_size;
					dst.y = j * tile_size;
					dst.w = tile_size;
					dst.h = tile_size;
					SDL_RenderCopy(renderer, interior_textures, &src, &dst);
					}
					
					if(level_3[j][i] == 'v')
					{

					SDL_Rect src, dst;

					src.x = 200;
					src.y = 0;
					src.w = 200;
					src.h = 200;
					dst.x = i * tile_size;
					dst.y = j * tile_size;
					dst.w = tile_size;
					dst.h = tile_size;
					SDL_RenderCopy(renderer, interior_textures, &src, &dst);
					}
					
					if(level_3[j][i] == '.')
					{

					SDL_Rect src, dst;

					src.x = 600;
					src.y = 0;
					src.w = 200;
					src.h = 200;
					dst.x = i * tile_size;
					dst.y = j * tile_size;
					dst.w = tile_size;
					dst.h = tile_size;
					SDL_RenderCopy(renderer, interior_textures, &src, &dst);
					}
					
					if(level_3[j][i] == 't')
					{

					SDL_Rect src, dst;

					src.x = 400;
					src.y = 0;
					src.w = 200;
					src.h = 200;
					dst.x = i * tile_size;
					dst.y = j * tile_size + 21;
					dst.w = tile_size;
					dst.h = tile_size;
					SDL_RenderCopy(renderer, interior_textures, &src, &dst);
					}
					
					if(level_3[j][i] == 'd')
					{
					door.dst.x = i * tile_size; 
					door.dst.y = j * tile_size; 
					door.dst.w = 100;
					door.dst.h = 200;
					SDL_RenderCopy(renderer, door_texture, NULL, &door.dst);
					
					collide_box3.x = door.dst.x;
					collide_box3.y = door.dst.y;
					collide_box3.w = door.dst.w;
					collide_box3.h = door.dst.h;

					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					SDL_RenderDrawRect(renderer, &collide_box3);
					}
					
					if(level_3[j][i] == painting)
					{

					SDL_Rect src, dst;

					src.x = 400;
					src.y = 200;
					src.w = 200;
					src.h = 200;
					dst.x = i * tile_size;
					dst.y = j * tile_size;
					dst.w = tile_size;
					dst.h = tile_size;
					SDL_RenderCopy(renderer, interior_textures, &src, &dst);
					}
				}
			}	
			break;
		case 4:
			for(int i = 0;i<map_width;i++)
			{
				for(int j = 0;j<map_height;j++)
				{
					if(level_4[j][i] == '#')
					{
					ground.src.x = 0;
					ground.src.y = 0;
					ground.src.w = tile_size;
					ground.src.h = tile_size;
					ground.dst.x = i * tile_size;
					ground.dst.y = j * tile_size;
					ground.dst.w = tile_size;
					ground.dst.h = tile_size;
					SDL_RenderCopy(renderer, texture, &ground.src, &ground.dst);
					} 
					
					if(level_4[j][i] == ' ')
					{
					SDL_Rect src, dst;

					src.x = 200;
					src.y = 0;
					src.w = tile_size;
					src.h = tile_size;
					dst.x = i * tile_size;
					dst.y = j * tile_size;
					dst.w = tile_size;
					dst.h = tile_size;
					SDL_RenderCopy(renderer, texture, &src, &dst);
					}	
				}
			}
			break;

		default:
			printf("out of range level\n");
	}
}

//create player tiles
void draw_player(){
	//character tiles
	player.src.x;
	player.src.y;
	player.src.w = 100;
	player.src.h = 100;

	player.dst.x; 
	player.dst.y;
	player.dst.w = 100; 
	player.dst.h = 100;
	
	//copy textures of player sprite to rectangle
	SDL_RenderCopy(renderer, player_tex, &player.src, &player.dst);
}

//create a window
void Window(){
	window = SDL_CreateWindow("Call A Exterminator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,Width,Height,0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
}

//check for rectangle collisions
bool collideRect()
{	
	if(current_level < 1 && SDL_HasIntersection(&player.dst, &door.dst))
	{
		printf("Collision with target detected!\n");
		printf("initializing level %d\n",current_level+1);
		current_level += 1;
		player.dst.x = 0;
		return true;
	}
	if(current_level < 2 && SDL_HasIntersection(&player.dst, &collide_box))
	{
		printf("Collision with target detected!\n");
		printf("initializing next level %d\n",current_level+1);
		current_level += 1;
		player.dst.x = 0;
		return true;
	}
	if(current_level < 3 && SDL_HasIntersection(&player.dst, &collide_box2))
	{
		printf("Collision with target detected!\n");
		printf("initializing next level %d \n",current_level+1);
		current_level += 1;
		player.src.y = 100;
		return true;
	}
	if(current_level < 4 && SDL_HasIntersection(&player.dst, &collide_box3))
	{
		printf("Collision with target detected!\n");
		printf("initializing final level, level %d\n",current_level+1);
		current_level += 1;
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
	//initialize SDL2 and SDL_image
        SDL_Init(SDL_INIT_VIDEO);
        if(SDL_Init(SDL_INIT_VIDEO)<0){
                printf("SDL failed to initialize\n",SDL_GetError());
                exit(-1);
        }
        IMG_Init(IMG_INIT_PNG & IMG_INIT_JPG);
        if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)<0){                                                  
		printf("SDL_image failed to initialize\n",SDL_GetError());
                exit(-1);
        }

	Window();		

	image5 = IMG_Load("assets/background2.jpg");
	image4 = IMG_Load("assets/interior_sprites.png");	
	image3 = IMG_Load("assets/house_texture.png");
	image2 = IMG_Load("assets/door.png");
	image = IMG_Load("assets/charRight_spritesheet.png");
	
	//house textures                                   
	texture = SDL_CreateTextureFromSurface(renderer,image3);              
	door_texture = SDL_CreateTextureFromSurface(renderer,image2);
	interior_textures = SDL_CreateTextureFromSurface(renderer,image4);
	
	//2nd background photo texture
        background_tex = SDL_CreateTextureFromSurface(renderer,image5);
	
	//player texture creation
	player_tex = SDL_CreateTextureFromSurface(renderer,image);

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
		//draw particles
		spray_pixels(0);
		//shows image on screen
		SDL_RenderPresent(renderer);
		while(SDL_PollEvent(&event)!=0){
			
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
				case SDLK_SPACE:
					spray = true;
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

	SDL_DestroyTexture(player_tex);SDL_DestroyTexture(texture);SDL_DestroyTexture(door_texture);SDL_DestroyTexture(interior_textures);SDL_DestroyTexture(background_tex);

	//end of game loop
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
