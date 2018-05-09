#include "cmsis_os.h"
#include "BlinkCarInstrument.h"
#include "EndCondition.h"

osThreadDef (end_condition, osPriorityNormal, 1, 0);

osThreadId init_end_condition(Information *info) {
		osThreadId tid_end_condition;  
    tid_end_condition = osThreadCreate(osThread(end_condition), info);
    if (!tid_end_condition) return (osThreadId)(-1);
    return tid_end_condition;
}

void end_condition(Information *info) {
	osStatus status;
	osEvent evt;
	while(1){
		evt = osSignalWait(0x01, osWaitForever);
		if (evt.status != osEventSignal)
			continue;
		osMutexWait (info_mutex, osWaitForever);
		
		if(info->biome_changer > 2000 && info->current_biome == 3 && !info->timer_running) {
			info->timer_running = true;
			start_timer();
		} 
		
		if( info->timer_counter >= 20 || (info->score == 0 && info->last_lap) )
			for(;;);
		else if(info->score == 0)
			reset_conditions(info);
		osMutexRelease(info_mutex);
		osSignalSet(info->tid_interaction, 0x01);
	}
}

void reset_conditions(Information *info) {
	info->kilometers = 0;
	info->biome_changer = 0;
	info->current_biome = 0;
	info->score = 300;
	info->panel_car_color = 0x000000;
	info->timer_running = false;
	info->timer_counter = 0;
	info->last_lap = true;
	stop_timer();
}
