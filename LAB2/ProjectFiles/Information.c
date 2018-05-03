#include "Information.h"
#include <stdbool.h>

void information_init(Information *info, Display *display, Car *car) {
	info->player_car = car;
	info->enemy_car = 0;
	info->enemy_car_count = 0x0;
	info->x_joystick = 0;
	info->acceleration = false;
	info->start = false;
	info->display = display;
}