#ifndef Level_Map

#define Level_Map

#define tile_size 100
#define stair_size 200
#define map_width 7
#define map_height 7

#define block 1
#define Door 4
#define Roof 3
#define _ground_ 1
#define Wall 2
#define stairs 5

int current_level = 0;

int level_0[map_width][map_height] =
{
	{0,0,0,0,0,3,3},
	{0,0,0,0,3,3,3},
	{0,0,0,3,3,3,3},
	{0,0,0,0,2,2,2},
	{0,0,0,0,0,2,2},
	{0,0,0,0,0,2,2},
	{1,1,1,1,1,1,1}

};

int level_1[map_width][map_height] =
{
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,5,},
	{1,1,1,1,1,1,1}

};


#endif
