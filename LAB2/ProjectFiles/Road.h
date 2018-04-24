#ifndef ROAD_H
#define ROAD_H

#include <stdint.h>
#include "Display.h"

#define ROAD_HEIGHT 96
#define ROAD_WIDTH 80
#define ROAD_STARTING_POINT 24

typedef struct {
	int left_starting_point;
	int right_starting_point;
	int state;
	uint32_t color;
	int frame;
	int displacement;
} Road;

void road_init(Road *road);
void road_draw(Display *display, Road *road, int move);

#endif
