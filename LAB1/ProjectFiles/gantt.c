#include "gantt.h"
#include "stdlib.h"
#include "string.h"
#include "cmsis_os.h"


void gantt_create_header(struct GanttDiagram *diagram, char *filename) {
	char header[] = "gantt"
											"title Thread Gantt Diagram";
	diagram->pointer = fopen(filename, "w");
	
  fwrite(header, strlen(header), 1, diagram->pointer);
}


void gantt_init_thread(struct GanttDiagram *diagram, char *thread_name) {
	int threadId = (int) osThreadGetId();

	char* diagramThreadName = diagram->threadName[threadId];
	diagramThreadName = thread_name;
	diagram->initTime[threadId] = (osKernelSysTick()/TICK_FACTOR);
}


void gantt_close_thread(struct GanttDiagram *diagram) {
	int threadId = (int) osThreadGetId();
	fprintf(diagram->pointer, "%s : %i, %i\n", diagram->threadName[threadId], (unsigned int)diagram->initTime[threadId], (unsigned int)(osKernelSysTick()/TICK_FACTOR));
}
