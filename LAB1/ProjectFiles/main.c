#include "cmsis_os.h"
#include "TM4C129.h"                    // Device header
#include <stdbool.h>
#include <stdio.h>
#include "grlib/grlib.h"
#include "KeyGenerator.h"
#include "Flags.h"

int main()
{
	osKernelInitialize(); 
	osKernelStart(); 
	init_flags();
	
	init_key_generator();
	
	osDelay(osWaitForever);
}
