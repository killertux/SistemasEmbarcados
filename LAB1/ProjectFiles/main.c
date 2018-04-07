#include "cmsis_os.h"
#include "TM4C129.h"                    // Device header
#include <stdbool.h>
#include <stdio.h>
#include "KeyGenerator.h"
#include "Flags.h"
#include "IsPrime.h"
#include "Decode.h"
#include "TestPenultimate.h"
#include "TestLast.h"
#include "showResult.h"
#include "End.h"

int main()
{
	osKernelInitialize(); 
	
	init_flags();
	
	init_key_generator();
	init_isPrime();
	init_decode();
	init_show_result();
	init_test_penultimate();
	init_test_last();
	init_end();
	
	osKernelStart(); 
	
	osDelay(osWaitForever);
}
