#ifndef THREADS_H
#define THREADS_H

#include <cmsis_os.h>
#include "ThreadCalculations.h"
#include "DisplayUtils.h"

typedef struct {
	osThreadId tid;
	char name;
	int estimated_ticks;
	int max_ticks;
	int execution_ticks;
	int relaxation_ticks;
	int aux_ticks;
	int start_ticks;
	int static_priority;
	int dynamic_priority;
	int frequency;
	int await_time;
	int delay;
	float progress;
	bool master_fault;
	bool secundary_fault;
	bool running;
	bool awaiting;
} ThreadInfo;

extern ThreadInfo threads[6];
extern osThreadId scheduler_id;

void initThreads(void);
void threadA(void);
void threadB(void);
void threadC(void);
void threadD(void);
void threadE(void);
void threadF(void);
void initThreadInfo(ThreadInfo *thread, int estimated_ticks, float deadline, int static_priority, int frequency, char name);

#endif
