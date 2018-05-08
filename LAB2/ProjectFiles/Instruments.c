#include "cmsis_os.h"
#include "Instruments.h"
#include "Information.h"
#include "panel.h"

osThreadDef (instruments, osPriorityNormal, 1, 0);

osThreadId init_instruments(Information *info) {
		osThreadId tid_instruments; 
    tid_instruments = osThreadCreate(osThread(instruments), info);
    if (!tid_instruments) return (osThreadId)(-1);
    return tid_instruments;
}

void instruments(Information *info) {
	osStatus status;
	osEvent evt;
	while(1){
		evt = osSignalWait(0x01, osWaitForever);
		if (evt.status != osEventSignal)
			continue;
		osMutexWait(info_mutex, osWaitForever);
		panel_draw(info->display, (int)info->kilometers, info->score);
		osMutexRelease(info_mutex);
		osSignalSet(info->tid_end_condition, 0x01);
	}
}
