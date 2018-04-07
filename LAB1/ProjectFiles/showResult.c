#include "showResult.h"
#include "cmsis_os.h"
#include "Flags.h"

osThreadId tid_show;                            // thread id
osThreadDef (show_result, osPriorityNormal, 1, 0);

int init_show_result()
{
	tid_show = osThreadCreate (osThread(show_result), NULL);
  if (!tid_show) return(-1);
	return 0;
}

void show_result() 
{
	while (1) {
			while(!finished_decoding) {
			}
			finished_decoding--;
			osDelay(100);
				
			while(finished_decoding) {
			}
			osThreadYield();
		}
}