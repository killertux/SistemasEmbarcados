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
#include "grlib/grlib.h"
#include "cfaf128x128x16.h"

int main()
 {
	osKernelInitialize(); 
	init_flags();
	
	#ifndef DEBUG
	cfaf128x128x16Init();
	GrContextInit(&sContext, &g_sCfaf128x128x16);
	GrFlush(&sContext);
	GrContextFontSet(&sContext, &g_sFontCmtt12);
	#endif

	init_key_generator();
	init_isPrime();
	init_decode();
	init_show_result();
	init_test_penultimate();
	init_test_last();
	init_end();
	
	osKernelStart();
	tick = osKernelSysTick();
	
	osDelay(osWaitForever);
}
