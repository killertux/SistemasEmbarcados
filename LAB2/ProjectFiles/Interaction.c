#include "cmsis_os.h"
#include "Interaction.h"
#include "TrackManager.h"
#include "joy.h"
#include "buttons.h"
#include "buzzer.h"

#include "horizon.h"
#include "Car.h"
#include "Road.h"
#include "Information.h"
#include "panel.h"

osThreadDef (interaction, osPriorityNormal, 1, 0);

osThreadId init_interaction(Information *info) {
		osThreadId tid_interaction; 
    tid_interaction = osThreadCreate(osThread(interaction), info);
    if (!tid_interaction) return (osThreadId)-1;
	
    return tid_interaction;
}

void interaction(Information *info) {
	osStatus status;
	//Signal Stuff
	int x, i, x_joystick;
	osEvent evt;
	int s1_press, s2_press;
	Car *player_car = info->player_car;
	int joystick_timer = 5, counter = 5, curve_counter = 5000;
	uint16_t min_buzzer = 9000;
  uint16_t buzzer_colision = 10000;

	while(1) {
		evt = osSignalWait(0x01, osWaitForever);
		if (evt.status != osEventSignal)
			continue;
		
		osMutexWait(info_mutex, osWaitForever);	
		x_joystick = joy_read_x();
		info->accel_pressed = button_read_s1();
		info->move_horizon = 0;
		
		if(info->lost) {
			 buzzer_per_set(500);
				for(;;);
		}
		
		info->move_left = info->move_right = false;
		if(x_joystick > 3000 && info->player_car->x < 128-30) {
			info->road->displacement = (info->player_car->x - 64) /4 ;
			info->move_horizon = 1;
			info->move_right = true;
		} else if (x_joystick < 1000 && info->player_car->x > 35) {
				info->road->displacement = (info->player_car->x - 64) /4 ;
				info->move_horizon = -1;
				info->move_left = true;
		}

			if (info->collision_counter <= 0 && info->speed_ticks <= 40) {
        buzzer_per_set(min_buzzer - info->speed_ticks * 50);
      } else if (info->collision_counter > 0)
        buzzer_per_set(buzzer_colision);
			else if (info->collision_counter <=0)
				buzzer_per_set(min_buzzer);

		display_update(info->display);
		display_clear_back_buffer(info->display);
		osMutexRelease(info_mutex);
		osSignalSet(info->tid_trackmanager, 0x01);
	}
}

