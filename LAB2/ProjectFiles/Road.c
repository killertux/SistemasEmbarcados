#include "road.h"
#include <math.h>

void road_init(Road *road) {
	road->left_starting_point = 32;
	road->right_starting_point = 96;
	road->color = 0xFFFFFF;
	road->frame = 1;
	road->displacement = 0;
}

void road_draw(Display *display, Road *road, int move) {
	int *frame;
	int starting_point = ROAD_STARTING_POINT;
	int end_point = starting_point + ROAD_WIDTH;
	float x, y;
	road->displacement += move;
	
	// Drawing a straight road
	if (road->state == 0) {
		for (x = starting_point; x < ROAD_WIDTH + ROAD_STARTING_POINT; x++) {
			if(x < 64)
				display->back_buffer[(int)x + road->displacement][(int)(134.4 - x*1.6)] = road->color;
			else
				display->back_buffer[(int)x + road->displacement][(int)(-70.4 + x*1.6)] = road->color;
		}
	}
	// Drawing a right curved road
	/* else if (road->state == 1) {
		 float angle, step;
		 int iterator = 0;
		 float end_x=24, end_y=32;
		 angle = atan((96-32)/(64-24));
		 //line 1
		 x = 24;
		 y = 96;
		 while(angle < 6.28) {
			 x += cos(angle);
			 y -= sin(angle);
			 iterator++;
				 angle += 0.05;
			 display->back_buffer[(int)x][(int)y] = road->color;
		 }
		 //line2
		/* 
		for (x = 0; x < ROAD_HEIGHT; x++) {
			float x_coordinate = (ROAD_WIDTH - x);
			x_coordinate *= x_coordinate;
			
			display->back_buffer[(int)x_coordinate][(int)x] = road->color;
		}*/
  // Drawing a left curved road
	/*} else if (road->state == -1) {
		for (x = 0; x < ROAD_WIDTH; x++) {
		   int x_coordinate = (ROAD_WIDTH - x);
		 	 x_coordinate *= x_coordinate;
			 
			 display->back_buffer[- x_coordinate][x] = (!frame[y*ROAD_WIDTH + x]) ? display->back_buffer[x][y] : road->color;
		}
	}*/
}