#include "cmsis_os.h"
#include "PlayerVehicle.h"
#include "Information.h"

osThreadDef (player_vehicle, osPriorityNormal, 1, 0);

osThreadId init_player_vehicle(Information *info) {
		osThreadId tid_player_vehicle;  
    tid_player_vehicle = osThreadCreate(osThread(player_vehicle), info);
    if (!tid_player_vehicle) return (osThreadId)(-1);
    return tid_player_vehicle;
}

void player_vehicle(Information *info) {
	osEvent evt;
	int i, turn_step;
	
	while (1) {
		evt = osSignalWait(0x01, osWaitForever);
		if (evt.status != osEventSignal)
			continue;
		
		osMutexWait(info_mutex, osWaitForever);
		info->collision_counter--;
		if (info->accel_pressed && info->collision_counter <= 0 && info->speed_ticks < 40) {
				info->speed_ticks += info->enemy_car_count;
		}
		info->kilometers += (!info->speed_ticks)? 0.05 : 0.05 + info->speed_ticks / 20;
		info->biome_changer += (!info->speed_ticks)? 0.05 :0.05 + info->speed_ticks / 20;
		turn_step = (info->biome_cycle[info->current_biome] == SNOW)? 2 : 4;
		if(info->move_right)
			info->player_car->x+=turn_step;
		else if(info->move_left)
			info->player_car->x-=turn_step;
		car_draw(info->display, info->player_car);
		osMutexRelease (info_mutex);

		osSignalSet(info->tid_adversaries, 0x01);
	}
}
