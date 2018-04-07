#include "TestLast.h"
#include "cmsis_os.h"
#include "Flags.h"

osThreadId tid_last;                            // thread id
osThreadDef (test_last, osPriorityNormal, 1, 0);

int init_test_last()
{
	tid_last = osThreadCreate (osThread(test_last), NULL);
  if (!tid_last) return(-1);
	return 0;
}

void test_last () 
{
	while(1) {
		//tamanho = len(mensagens);

		while(!finished_decoding) {
		}
		finished_decoding--;

		/*char ultima[4];
		memcpy(penultima, &mensagens + (tamanho - 1) - 4, 4)
		int* ultimaWord = (int*)ultima;
	
		if (key * key / lastPrime == ultimaWord) {
			passed_last = 1;
			terminou = 1;
		}*/
		osDelay(1000);
			while(finished_decoding) {
		}
		passed_last = 0;
		passed_last_await = 0;
		osThreadYield();
	}
}