#include "cmsis_os.h"
#include "End.h"
#include "Flags.h"
#include <string.h>

osThreadId tid_End;                            // thread id
osThreadDef (end, osPriorityNormal, 1, 0);

int init_end()
{
	tid_End = osThreadCreate (osThread(end), NULL);
  if (!tid_End) return(-1);
	return 0;
}

void end()
{
	char buffer[255];
	while(1) {
		if (f_end) {
			#ifndef DEBUG
				GrContextBackgroundSet(&sContext, ClrBlack);
				GrContextForegroundSet(&sContext, ClrWhite);
				GrStringDraw(&sContext, "Key:", -1, 0, (sContext.psFont->ui8Height+2)*4, true);
				sprintf(buffer, "%u", key);
				GrStringDraw(&sContext, buffer, -1, 0, (sContext.psFont->ui8Height+2)*5, true);
				GrStringDraw(&sContext, "Execution time:", -1, 0, (sContext.psFont->ui8Height+2)*6, true);
				sprintf(buffer, "%u ms", osKernelSysTick()/120000 - tick);
				GrStringDraw(&sContext, buffer, -1, 0, (sContext.psFont->ui8Height+2)*7, true);
			#endif
				while(1);
		}
		osThreadYield();
	}
}
