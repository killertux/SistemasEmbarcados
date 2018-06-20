#include "DisplayThread.h"

osThreadDef (display, osPriorityBelowNormal, 1, 0);

void initDisplayThread() {
	osThreadId tid = osThreadCreate(osThread(display), NULL);
}

void display() {
	int i;
	char buffer[20];
	char fault;
	while (1) {
		for (i = 0; i < 6; i++) {
			sprintf(buffer, "%c", threads[i].name);
			osThreadYield();
			print(buffer, i, 0);
			osThreadYield();
			sprintf(buffer, "%4d",  threads[i].static_priority);
			osThreadYield();
			print(buffer, i, 2);
			osThreadYield();
			sprintf(buffer, "%8d", threads[i].relaxation_ticks);
			osThreadYield();
			print(buffer, i, 6);
			osThreadYield();
			fault = (threads[i].master_fault) ? 'M' : (threads[i].secundary_fault) ? 'S' : 'N';
			osThreadYield();
			threads[i].secundary_fault = false;
			sprintf(buffer, "%c", fault);
			osThreadYield();
			print(buffer, i, 14);
			osThreadYield();
			if (threads[i].awaiting) {
				sprintf(buffer, "Aw");
				osThreadYield();
			} else if (threads[i].running) {
				sprintf(buffer, "Rn");
				osThreadYield();
			} else {
				sprintf(buffer, "Re");
				osThreadYield();
			}
			print(buffer, i, 16);
			osThreadYield();
			
			sprintf(buffer, "%c", threads[i].name);
			osThreadYield();
			print(buffer, i+ 7, 0);
			osThreadYield();
			sprintf(buffer, "%.2f%%", threads[i].progress * 100);
			osThreadYield();
			print(buffer, i+ 7, 2);
			osThreadYield();
			
			sprintf(buffer, "%7d", threads[i].delay);
			osThreadYield();
			print(buffer, i+ 7, 9);
			
			osThreadYield();
			if (threads[i].master_fault) {
				osDelay(osWaitForever);
			}
		}
	}
}
