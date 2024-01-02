#ifndef Level_Map

#define Level_Map

#define tile_size 100
#define map_width 7
#define map_height 7

#define block 1
#define Door 4
#define Roof 3
#define _ground_ 1
#define Wall 2
#define stairs 5
#define painting 6
#define vase 7
#define glass_window 8

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
	{0,0,0,0,6,0,0,},
	{0,0,0,0,0,0,5,},
	{1,1,1,1,1,1,1}

};

int level_2[map_width][map_height] =
{
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,},
	{8,0,6,8,0,0,4,},
	{0,0,0,0,0,0,0,},
	{1,1,1,1,1,1,1}

};


#endif
