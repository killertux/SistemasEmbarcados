#include "cmsis_os.h"
#include "KeyGenerator.h"

osThreadId tid_KeyGenerator;                            // thread id
osThreadDef (key_generator, osPriorityNormal, 1, 0);

void key_generator()
{
	
}