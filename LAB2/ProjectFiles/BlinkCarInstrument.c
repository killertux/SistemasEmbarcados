#include "cmsis_os.h"                                           
#include "BlinkCarInstrument.h"
	
static osTimerId id;

osThreadId tid_timer;
osThreadDef (timer, osPriorityNormal, 1, 0);
static Information *s_info;

static void Timer_Callback (const void *arg) {
	if( s_info->panel_car_color == 0x000000)
		s_info->panel_car_color = 0xffffff;
	else
		s_info->panel_car_color = 0x000000;
	s_info->timer_counter++;
}	

void timer() {
	osEvent evt;
	while(1) {
		osDelay(2000);
		osMutexWait(info_mutex, osWaitForever);
		if (s_info->timer_running) {
			if( s_info->panel_car_color == 0x000000)
				s_info->panel_car_color = 0xffffff;
			else
				s_info->panel_car_color = 0x000000;
			s_info->timer_counter++;
		}
		osMutexRelease(info_mutex);
	}
}

static osTimerDef (Timer, Timer_Callback);

void create_timer (Information *info) {
	//osStatus status;
	s_info = info;
  //id = osTimerCreate (osTimer(Timer), osTimerPeriodic, NULL);*/
	tid_timer= osThreadCreate(osThread(timer), NULL);
}

void start_timer() {
	//osTimerStart (id, 1000);
}

void stop_timer() {
	//osTimerStop(id);
}