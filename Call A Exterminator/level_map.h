#ifndef Level_Map

#define Level_Map

#define tile_size 100
#define map_width 7
#define map_height 7

#define block 1

int current_level = 0;

int level[map_width][map_height] =
{
	{1,1,1,1,1,1,1},
	{1,0,0,0,0,0,1},
	{1,1,1,1,1,0,1},
	{1,0,0,0,1,0,1},
	{1,0,0,0,1,0,1},
	{1,0,0,0,1,0,1},
	{1,1,1,1,1,1,1},
};


#endif
