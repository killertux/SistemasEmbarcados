#include "TestPenultimate.h"
#include "cmsis_os.h"
#include "Flags.h"
#include "utils.h"

osThreadId tid_pen;                            // thread id
osThreadDef (test_penultimate, osPriorityNormal, 1, 0);

int init_test_penultimate()
{
	tid_pen = osThreadCreate (osThread(test_penultimate), NULL);
  if (!tid_pen) return(-1);
	return 0;
}

void test_penultimate() 
{
	uint32_t penultimate_word;
	while (1) {
		while(!f_test_penultimate) {
			osThreadYield();
		}
		f_test_penultimate = false;
		penultimate_word = getWord(msg + 33*4) - key;
		
		#ifdef GANTT
				{
					int i = 0;
					for(i = 0 ; i < 50000; i++);
				}
		#endif
		
		if ((key / 2) == penultimate_word) {
			passed_penultimate = true;
		} else {
			passed_penultimate = false;
		}

		f_finished_test_penultimate = true;
		osThreadYield();
	}
}