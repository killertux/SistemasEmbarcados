#include "cmsis_os.h"
#include "TrackManager.h"
#include "road.h"
#include "horizon.h"

#include "Interaction.h"

osThreadDef (track_manager, osPriorityNormal, 1, 0);

osThreadId init_track_manager(Information *info) {
		osThreadId tid_trackmanager;
    tid_trackmanager = osThreadCreate(osThread(track_manager), info);
    if (!tid_trackmanager) return (osThreadId)(-1);
    return tid_trackmanager;
}

void track_manager(Information *info) {
	osEvent evt;
	int curve_counter;
	uint32_t road_color, mountain_color, sky_color, grass_color;
	
	while(1) {
		evt = osSignalWait (0x01, osWaitForever);
		if (evt.status != osEventSignal)
			continue;
		
		osMutexWait(info_mutex, osWaitForever);
		if(curve_counter > 4500 || (curve_counter < 3000 && curve_counter > 2000))
			info->road->state = 0;
		if(curve_counter <= 4000 && curve_counter > 3000)
			info->road->state = 1;
		if(curve_counter < 2000)
			info->road->state = -1;
		curve_counter-=5;
		if (curve_counter <= 0) {
			curve_counter = 5000;
		}
		
		if(info->biome_cycle[info->current_biome] == DAY) {
			road_color = 0xffffff;
			mountain_color = 0x84881a;
			sky_color = 0x1110aa;
			grass_color = 0x014400;
		} else if(info->biome_cycle[info->current_biome] == SNOW) {
			road_color = 0x050505;
			mountain_color = 0xdadada;
			sky_color = 0x212d8c;
			grass_color = 0xffffff;
		} else if(info->biome_cycle[info->current_biome] == NIGHT) {
			road_color = 0xffffff;
			mountain_color = 0x919193;
			sky_color = 0x4b4b4d;
			grass_color = 0x070707;
		}
		
		if(info->biome_changer > 6500) {
			info->biome_changer = 0;
			info->current_biome++;
		}
		
		info->road->color = road_color;
		horizon_draw(info->display, info->road->horizontal_movement, mountain_color, sky_color, grass_color);
		road_draw(info->display, info->road, info->road->horizontal_movement);
		osMutexRelease (info_mutex);
	
		osSignalSet(info->tid_player_vehicle, 0x01);
	}
}
