#include "cmsis_os.h"
#include "KeyGenerator.h"
#include "Flags.h"
#include "utils.h"

osThreadId tid_KeyGenerator;                            // thread id
osThreadDef (key_generator, osPriorityNormal, 1, 0);

int init_key_generator()
{
	tid_KeyGenerator = osThreadCreate (osThread(key_generator), NULL);
  if (!tid_KeyGenerator) return(-1);
	return 0;
}

//&& ((passed_last == 1 || passed_last_await == 1)
//			|| (passed_penultimate == 1 || passed_penultimate_await == 1))
void key_generator()
{
	key = (getWord(msg) - 0xff) | 0x01;
	last_key = key;
	while(1) {
		while(!f_generate) {
				osThreadYield();
			}
		f_generate = false;

		key +=2;
		f_prime = 1;
		osThreadYield();
	}
}
