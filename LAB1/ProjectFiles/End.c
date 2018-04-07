#include "cmsis_os.h"
#include "End.h"
#include "Flags.h"

osThreadId tid_End;                            // thread id
osThreadDef (end, osPriorityNormal, 1, 0);

int init_end()
{
	tid_End = osThreadCreate (osThread(end), NULL);
  if (!tid_End) return(-1);
	return 0;
}

void end()
{
	while(1) {
		if (passed_last && passed_penultimate && !passed_last_await && !passed_penultimate_await) {
				osDelay(osWaitForever);
		}
	}
}
