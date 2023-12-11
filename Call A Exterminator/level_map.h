#ifndef Level_Map

#define Level_Map

#define tile_size 100
#define map_width 7
#define map_height 7

#define block '#'

int current_level = 0;

char* level[map_width][map_height] =
{
	"#######",
	"#     #",
	"#     #",
	"#     #",
	"#  #  #",
	"#     #",
	"#######"
};


#endif
