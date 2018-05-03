#include "cmsis_os.h"
#include "TrackManager.h"

osThreadId tid_trackmanager;                            // thread id
osThreadDef (track_manager, osPriorityNormal, 1, 0);

int init_track_manager() {
    tid_trackmanager = osThreadCreate(osThread(track_manager), NULL);
    if (!tid_trackmanager) return (-1);
    return 0;
}

void track_manager() {

}
