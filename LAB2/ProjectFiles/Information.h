#ifndef INTERACTION_H
#define INTERACTION_H

#include <stdint.h>
#include "Display.h"
#include <stdbool.h>
#include "Car.h"

typedef struct {
	Car* player_car;
	Car* enemy_car;
	int enemy_car_count;
	int x_joystick;
	boolean acceleration;
	boolean start;
	Display* display;
} Information;

#endif