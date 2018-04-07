#ifndef GANTT_H
#define GANTT_H

#include <stdio.h>

#define TICK_FACTOR 100000

struct GanttDiagram {
	FILE *pointer;
	char threadName[6][15];
	unsigned int initTime[6];
};

void gantt_create_header(struct GanttDiagram *diagram, char *filename);
void gantt_init_thread(struct GanttDiagram *diagram, char *thread_name);
void gantt_close_thread(struct GanttDiagram *diagram);

#endif
