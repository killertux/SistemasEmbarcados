#include "cmsis_os.h"
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
		osSignalSet(info->tid_interaction, 0x01);
	}
}
