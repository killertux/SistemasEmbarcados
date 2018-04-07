#include "cmsis_os.h"
#include "KeyGenerator.h"
#include "Flags.h"

osThreadId tid_KeyGenerator;                            // thread id
osThreadDef (key_generator, osPriorityNormal, 1, 0);

int init_key_generator()
{
	tid_KeyGenerator = osThreadCreate (osThread(key_generator), NULL);
  if (!tid_KeyGenerator) return(-1);
	return 0;
}

void key_generator()
{
	key = 3;
	while(1) {
		if((prime == 0 && prime_await == 0)
			||(passed_last == 0 && passed_last_await == 0)
			||(passed_penultimate == 0 && passed_penultimate_await == 0)){
				key +=2;
				generated = 1;
				prime_await = 1;
				osThreadYield();
			}
	}
}
