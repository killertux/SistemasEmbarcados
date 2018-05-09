#include "Information.h"
#include <stdbool.h>
#include "cmsis_os.h"

osMutexDef (InfoMutex);                            // mutex name 
osMutexId info_mutex;
																										 
void information_init(Information *info, Display *display, Car *car, Road* road) {
	int i;
	info_mutex = osMutexCreate (osMutex (InfoMutex));

	info->player_car = car;
	for (i = 0; i < 2; i++) {
    car_init (&info->enemy_car[i]);
		info->enemy_car[i].x = 42 + i * 25;
		info->enemy_car[i].y = (CAR_HEIGHT * 2) * i;
	}
	
	// Resets at zero and at arbitrary max
	info->speed_ticks = 2;
	
	info->enemy_car[0].color = 0x640064;
	info->enemy_car[1].color = 0x646d00;
	
	info->display = display;
	info->road = road;
	info->enemy_car_count = 0x2;
	info->collision_counter = 0;
	info->kilometers = 0;
	info->biome_changer = 0;
	info->biome_cycle[0] = DAY;
	info->biome_cycle[1] = SNOW;
	info->biome_cycle[2] = DAY;
	info->biome_cycle[3] = NIGHT;
	info->biome_cycle[4] = DAY;
	info->current_biome = 0;
	info->score = 200;
	info->panel_car_color = 0x000000;
	info->timer_running = false;
	info->timer_counter = 0;
	info->last_lap = false;
	info->lost = false;
}
