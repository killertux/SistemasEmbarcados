#ifndef CAR_H
#define CAR_H

#include <stdint.h>
#include "Display.h"

#define CAR_WIDTH 23
#define CAR_HEIGHT 11
#define CAR_DEFAULT_Y 79

typedef struct {
	int x,y;
	uint32_t color;
	int frame;
} Car;

void car_init(Car *car);
void car_draw(Display *display, Car *car);

#endif
