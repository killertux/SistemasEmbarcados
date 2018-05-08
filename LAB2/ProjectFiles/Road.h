#ifndef ROAD_H
#define ROAD_H

#include <stdint.h>
#include "Display.h"

#define ROAD_HEIGHT 96
#define ROAD_WIDTH 80
#define ROAD_STARTING_POINT 24

#define ROAD_LEFT_LINE_START_X 24
#define ROAD_LEFT_LINE_START_Y 96
#define ROAD_LEFT_LINE_BEZIER_X 44
#define ROAD_LEFT_LINE_BEZIER_Y 64


#define ROAD_STRAIGHT_END_X 64
#define ROAD_LEFT_END_X 24
#define ROAD_RIGHT_END_X 104
#define ROAD_END_Y 32

#define ROAD_RIGHT_LINE_START_X 104
#define ROAD_RIGHT_LINE_START_Y 96
#define ROAD_RIGHT_LINE_BEZIER_X 84
#define ROAD_RIGHT_LINE_BEZIER_Y 64

typedef struct {
	int left_starting_point;
	int right_starting_point;
	int state;
	uint32_t color;
	int frame;
	int displacement;
	float end_x;
	int horizontal_movement;
} Road;

void road_init(Road *road);
void road_draw(Display *display, Road *road, int move);
void road_move(Road *road, int movement);

#endif
