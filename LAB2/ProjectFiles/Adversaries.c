#include "cmsis_os.h"
#include "Adversaries.h"
#include "Car.h"
#include "Information.h"
#include <stdlib.h>   
#include <math.h>
#include "buzzer.h"

osThreadDef (adversaries, osPriorityNormal, 1, 0);

osThreadId init_adversaries(Information *info) {
		osThreadId tid_adversaries;  
    tid_adversaries = osThreadCreate(osThread(adversaries), info);
    if (!tid_adversaries) return (osThreadId)-1;
    return tid_adversaries;
}

void adversaries(Information* info) {
  int i;
	osEvent evt;

	while(1) {
		evt = osSignalWait(0x01, osWaitForever);
		if (evt.status != osEventSignal)
			continue;

		osMutexWait (info_mutex, osWaitForever);
		info->player_car->color = 0xb6b6b6;
		for (i = 0; i < info->enemy_car_count; i++) {
			if (check_collision(info, info->player_car, &info->enemy_car[i]) && info->collision_counter <= 0) {
					info->speed_ticks = 0;
					info->collision_counter = 30;
					info->biome_changer += 40;
			}
			update_car_y(info, &info->enemy_car[i]);

			enemy_car_draw(info->display, &info->enemy_car[i], info->road->displacement, info->road->end_x, 32);
		}
							
		osMutexRelease (info_mutex);
		osSignalSet(info->tid_instruments, 0x01);
	}
}

// This method needs to be called from the adversaries thread (currently bugging)
// There is a bug here where the cars stop updating its Y after it goes forward some time.
void update_car_y(Information *info, Car* car) {
	if (info->actual_speed_tick <= 0) {
		// If the ticks are bigger than 20, it is considers it is going backwards
		if (info->speed_ticks <= 20) {
			if (car->y < 47) {
				info->actual_speed_tick = info->speed_ticks;
				car->y++;
			}
			else if (car->y >= 47) {
				int generate_x = 0, i = 0;
				car->y = 0;
				if(info->score < 200)
					info->score++;
				car->color *= 3;
				while(!generate_x) {
					int v = rand() % 128;
					i++;
					if(i == 50) {
						 generate_x = v;
						 break;
					}
					if(!(v > 34 + info->road->displacement && v < 94 + info->road->displacement))
						continue;
					if(v+15 < info->player_car->x || v+11 > info->player_car->x + 22){
						generate_x = v;
						break;
					}
				}
				car->x = generate_x;
			}
		
		// Enemy cars going backwards
		} else {
			if (car->y > 0) {
				info->actual_speed_tick = 40 - info->speed_ticks;
				car->y--;
			}
			else {
				car->x = (info->player_car->x > 64)? info->player_car->x - 12 : info->player_car->x + 12;
				if(info->score > 0)
					info->score--;
				car->y = 46;
				car->color *= -3;
			}
		}
	}
  else {
		info->actual_speed_tick--;
	}
}

bool check_collision(Information* info, Car* player_car, Car* enemy_car) {
	if (player_car->x <= enemy_car->x + info->road->displacement + CAR_WIDTH-8 &&
   		player_car->x + CAR_WIDTH-8 >= enemy_car->x + info->road->displacement &&
     	player_car->y + CAR_HEIGHT-4 >= enemy_car->y &&
     	player_car->y <= enemy_car->y + CAR_HEIGHT -4) {
			return true;
	}
	return false;
}