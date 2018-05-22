#include "cmsis_os.h"
#include "TM4C129.h"                    // Device header
#include <stdbool.h>
#include <stdio.h>
#include "grlib/grlib.h"
#include "UART.h"

int main()
{
	init_uart();
	while (1){
		send_byte((void*)'b');
	}
	/*osKernelInitialize(); 
	osKernelStart(); 
	
	osDelay(osWaitForever);*/
}
