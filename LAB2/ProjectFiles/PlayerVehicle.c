#include "cmsis_os.h"
#include "PlayerVehicle.h"

osThreadId tid_player_vehicle;                            // thread id
osThreadDef (player_vehicle, osPriorityNormal, 1, 0);

int init_player_vehicle() {
    tid_player_vehicle = osThreadCreate(osThread(player_vehicle), NULL);
    if (!tid_player_vehicle) return (-1);
    return 0;
}

void player_vehicle() {

}
