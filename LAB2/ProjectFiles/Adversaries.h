#ifndef ADVERSARIES_H
#define ADVERSARIES_H

#include "Information.h"

osThreadId init_adversaries(Information *info);

void adversaries(Information* info);
void update_car_y(Information *info, Car* car);
bool check_collision(Information* info, Car* player_car, Car* enemy_car);

#endif
