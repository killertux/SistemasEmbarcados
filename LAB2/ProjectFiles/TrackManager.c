#include "cmsis_os.h"
#include "TrackManager.h"
#include "road.h"
#include "horizon.h"

#include "Interaction.h"

osThreadId tid_trackmanager;

osThreadDef (track_manager, osPriorityNormal, 1, 0);

int init_track_manager(Information *info) {
    tid_trackmanager = osThreadCreate(osThread(track_manager), info);
    if (!tid_trackmanager) return (-1);
    return 0;
}

void track_manager(Information *info) {
	Road road;
	osEvent evt;
	road_init(&road);
	while(1) {
		evt = osSignalWait (0x01, osWaitForever);
		if (evt.status != osEventSignal)
			continue;
		horizon_draw(info->display, 0);
		road_draw(info->display, &road, 0);
		
		osSignalSet(tid_interaction, 0x01);
	}
}
