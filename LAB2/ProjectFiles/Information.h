#ifndef INFORMATION_H
#define INFORMATION_H

#include "cmsis_os.h"
#include "road.h"
#include <stdint.h>
#include "Display.h"
#include <stdbool.h>
#include "Car.h"

extern osMutexId info_mutex;

typedef enum {
	DAY = 0,
	SNOW,
	NIGHT,
}BIOME;
												
typedef struct {
	//Structs
	Road* road;
	Display* display;
	Car* player_car;
	Car enemy_car[3];
	int enemy_car_count;
	
	//Speed and distance
	int actual_speed_tick;
	int speed_ticks;
	int collision_counter;
	float kilometers;
	float biome_changer;
	
	BIOME biome_cycle[5];
	int current_biome;
	int score;
	
	//Input
	bool move_left;
	bool move_right;
	bool start;
	bool accel_pressed;
	
	//Thread ids
	osThreadId tid_adversaries;
	osThreadId tid_trackmanager;
	osThreadId tid_interaction;
	osThreadId tid_player_vehicle;
	osThreadId tid_instruments;  
	osThreadId tid_end_condition;
} Information;

void information_init(Information *info, Display *display, Car *car, Road *road);

#endif