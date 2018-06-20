#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <cmsis_os.h>
#include "Threads.h"
#include "UART.h"

//#define GANTT

#define TIMER 5 //ms

void initScheduler();
void scheduler();
void timerHandler();

void awakeThreads(int ticks);
void orderReadyThreads();
void updateDynamicPriority(int ticks);
void addToQueue(ThreadInfo *thread, ThreadInfo **queue);
void ganttHeader();
void ganttLine(char taskName, int start_ticks, int end_ticks);

#endif
