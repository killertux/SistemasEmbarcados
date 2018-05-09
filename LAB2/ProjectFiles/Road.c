#include "road.h"
#include <math.h>
#include "Bezier.h"

void road_init(Road *road) {
	road->left_starting_point = 32;
	road->right_starting_point = 96;
	road->color = 0xFFFFFF;
	road->frame = 1;
	road->displacement = 0;
	road->end_x = ROAD_STRAIGHT_END_X;
}

void road_draw(Display *display, Road *road) {
	int *frame;
	int starting_point = ROAD_STARTING_POINT;
	int end_point = starting_point + ROAD_WIDTH;
	float x, y;
	
	if (road->state == 0) {
		if (road->end_x < ROAD_STRAIGHT_END_X)
			road->end_x+=2;
		else if (road->end_x > ROAD_STRAIGHT_END_X)
			road->end_x-=2;
	} else if (road->state == 1) {
		if (road->end_x < ROAD_RIGHT_END_X)
			road->end_x+=2;
	} else if (road->state == -1) {
		if (road->end_x > ROAD_LEFT_END_X)
			road->end_x-=2;
	}
	
	draw_bezier_curve(
		display,
		road->displacement,
		road->color,
		ROAD_LEFT_LINE_START_X,
		ROAD_LEFT_LINE_START_Y,
		ROAD_LEFT_LINE_BEZIER_X,
		ROAD_LEFT_LINE_BEZIER_Y,
		road->end_x,
		ROAD_END_Y
	);
	draw_bezier_curve(
		display,
		road->displacement,
		road->color,
		ROAD_RIGHT_LINE_START_X,
		ROAD_RIGHT_LINE_START_Y,
		ROAD_RIGHT_LINE_BEZIER_X,
		ROAD_RIGHT_LINE_BEZIER_Y,
		road->end_x,
		ROAD_END_Y
	);
}