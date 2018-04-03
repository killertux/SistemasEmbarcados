#include "cmsis_os.h"
#include "TM4C129.h"                    // Device header
#include <stdbool.h>
#include <stdio.h>
#include "grlib/grlib.h"
#include "KeyGenerator.h"

int main()
{
	osKernelInitialize(); 
	osKernelStart(); 
	
	init_key_generator();
	
	osDelay(osWaitForever);
}
