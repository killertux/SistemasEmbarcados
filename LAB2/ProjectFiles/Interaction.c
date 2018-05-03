#include "cmsis_os.h"
#include "Interaction.h"
#include "TrackManager.h"
#include "joy.h"
#include "buttons.h"

osThreadId tid_interaction; 
osThreadDef (interaction, osPriorityNormal, 1, 0);

int init_interaction(Information *info) {
    tid_interaction = osThreadCreate(osThread(interaction), info);
    if (!tid_interaction) return (-1);
    return 0;
}

void interaction(Information *info) {
		//Signal Stuff
		int joy_x;
		osEvent evt;
		while(1) {
			evt = osSignalWait (0x01, osWaitForever);
			if (evt.status != osEventSignal)
				continue;
			display_update(info->display);
			
			joy_x = joy_read_x();
			if(joy_x > 3000)
				info->x_joystick = 1;
			else if (joy_x < 300)
				info->x_joystick = -1;
			else
				info->x_joystick = 0;
			info->acceleration = button_read_s1();
			info->start = button_read_s2();
			
			//TODO: audio stuff
			osSignalSet(tid_trackmanager, 0x01);
		}
}
