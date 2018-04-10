#include "showResult.h"
#include "cmsis_os.h"
#include "Flags.h"
#include "grlib/grlib.h"
#include "cfaf128x128x16.h"

osThreadId tid_show;                            // thread id
osThreadDef (show_result, osPriorityNormal, 1, 0);
//tContext sContext;
int init_show_result()
{
	/*cfaf128x128x16Init();
	GrContextInit(&sContext, &g_sCfaf128x128x16);
	GrFlush(&sContext);*/
	tid_show = osThreadCreate (osThread(show_result), NULL);
  if (!tid_show) return(-1);
	return 0;
}

void show_result() 
{
	while (1) {
			while(!f_finished_test_last || ! f_finished_test_penultimate) {
				osThreadYield();
			}
			f_finished_test_last = false;
			f_finished_test_penultimate = false;
			
			#ifndef DEBUG
				//cfaf128x128x16Clear();
				GrContextBackgroundSet(&sContext, ClrBlack);
				GrContextForegroundSet(&sContext, ClrWhite);
				GrStringDraw(&sContext, (char*)decoded_msg, 13, 0, (sContext.psFont->ui8Height+2)*1, true);
				GrStringDraw(&sContext, (char*)decoded_msg + 13, 13, 0, (sContext.psFont->ui8Height+2)*2, true);
				GrStringDraw(&sContext, (char*)decoded_msg + 26, 7, 0, (sContext.psFont->ui8Height+2)*3, true);

			#endif
			#ifdef GANTT
				{
					int i = 0;
					for(i = 0 ; i < 10000; i++);
				}
			#endif
			
			if(!(passed_last && passed_penultimate))
				f_generate = true;
			else
				f_end = true;
			
			osThreadYield();
		}
}