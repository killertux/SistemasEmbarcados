#ifndef INFORMATION_H
#define INFORMATION_H

#include <stdint.h>
#include "Display.h"
#include <stdbool.h>
#include "Car.h"

typedef struct {
	Car* player_car;
	Car* enemy_car;
	int enemy_car_count;
	int x_joystick;
	bool acceleration;
	bool start;
	Display* display;
} Information;

void information_init(Information *info, Display *display, Car *car);

#endif