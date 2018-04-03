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
	
}