#include "TestPenultimate.h"
#include "cmsis_os.h"
#include "Flags.h"

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
	while (1) {
		//tamanho = len(mensagens);

		while(!finished_decoding) {
		}
		finished_decoding--;

		/*char penultima[4];
		memcpy(penultima, &mensagens + (tamanho - 1) - 8, 4)
		int* penultimaWord = (int*)penultima;
	
		if (key / 2 == penultimaWord) {
			passed_penultimate = 1;
			terminou = 1;
		}*/	
		osDelay(500);
		
		while(finished_decoding) {
		}
		passed_penultimate = 0;
		passed_penultimate_await = 0;
		osThreadYield();
	}
}