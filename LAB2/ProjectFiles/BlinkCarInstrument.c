#include "cmsis_os.h"                                           
#include "BlinkCarInstrument.h"
	
static osTimerId id;

static Information *s_info;

static void Timer_Callback (const void *arg) {
	if( s_info->panel_car_color == 0x000000)
		s_info->panel_car_color = 0xffffff;
	else
		s_info->panel_car_color = 0x000000;
	s_info->timer_counter++;
}	

static osTimerDef (Timer, Timer_Callback);

void create_timer (Information *info) {
	osStatus status;
	s_info = info;
  id = osTimerCreate (osTimer(Timer), osTimerPeriodic, NULL);
}

void start_timer() {
	osTimerStart (id, 1000);   
}

void stop_timer() {
	osTimerStop(id);
}