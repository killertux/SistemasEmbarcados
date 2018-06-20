#include "Scheduler.h"

osTimerDef(schedulerTimer, timerHandler);

osThreadId scheduler_id;
osTimerId timer_id;

ThreadInfo *awaitThreads[6];
ThreadInfo *readyThreads[6];
int miliseconds;
void initScheduler() {
	int i;
	scheduler_id = osThreadGetId();
	osThreadSetPriority(scheduler_id, osPriorityRealtime);
	timer_id = osTimerCreate(osTimer(schedulerTimer), osTimerPeriodic, NULL);
	
	#ifdef GANTT
	init_uart();
	ganttHeader();
	#endif

	for (i = 0; i < 6; i++) {
		awaitThreads[i] = &threads[i];
		readyThreads[i] = NULL;
	}
	miliseconds = 0;
	osTimerStart(timer_id, TIMER);
}

void timerHandler() {
	miliseconds += TIMER;
	osSignalSet(scheduler_id, 0x01);
}

void scheduler() {
	int actualTicks;
	while (1) {
		actualTicks = osKernelSysTick();
		
		awakeThreads(actualTicks);
		orderReadyThreads();

		if (readyThreads[0] != NULL) {
			readyThreads[0]->aux_ticks = actualTicks;
			readyThreads[0]->running = true;
			osThreadSetPriority(readyThreads[0]->tid, osPriorityNormal);
		}
		
		osSignalWait(0x01, osWaitForever);
		actualTicks = osKernelSysTick();
		
		if (readyThreads[0] != NULL) {
			readyThreads[0]->execution_ticks += actualTicks - readyThreads[0]->aux_ticks;
			readyThreads[0]->running = false;
			osThreadSetPriority(readyThreads[0]->tid, osPriorityIdle);
			if (readyThreads[0]->awaiting == true) {
				#ifdef GANTT
				ganttLine(readyThreads[0]->name, readyThreads[0]->start_ticks, actualTicks);
				#endif
				readyThreads[0]->await_time = miliseconds;
				addToQueue(readyThreads[0], awaitThreads);
				readyThreads[0] = NULL;
			}
		}
		
		updateDynamicPriority(actualTicks);
	}
}

void awakeThreads(int ticks) {
 int i;
 for (i = 0; i < 6; i++) {
	 ThreadInfo *cursor = awaitThreads[i];
	 if (cursor == NULL)
		 continue;
	 if ( (1000 / cursor->frequency) < miliseconds - cursor->await_time) {
		 cursor->awaiting = false;
		 cursor->start_ticks = ticks;
		 cursor->execution_ticks = 0;
		 cursor->await_time = 0;
		 cursor->dynamic_priority = 0;
		 addToQueue(cursor, readyThreads);
		 awaitThreads[i] = NULL;
		 osSignalSet(cursor->tid, 0x01);
	 }
 }
}
 
void addToQueue(ThreadInfo *thread, ThreadInfo **queue) {
 int i;
 for (i = 0; i < 6; i++) {
	 if (queue[i] == NULL) {
		 queue[i] = thread;
		 break;
	 }
 }
}
 
void orderReadyThreads(){
	int i, j;
	ThreadInfo *aux;
	for (i = 0; i < 6; i++) {
		for (j = i + 1; j < 6; j++) {
			if (readyThreads[j] == NULL)
				continue;
			if (readyThreads[i] == NULL || (readyThreads[j]->static_priority + readyThreads[j]->dynamic_priority) <=  (readyThreads[i]->static_priority + readyThreads[i]->dynamic_priority)) {
				aux = readyThreads[j];
				readyThreads[j] = readyThreads[i];
				readyThreads[i] = aux;
			}
		}
	}
}

void updateDynamicPriority(int ticks) {
	int i = 0;
	for (i = 0; i < 6; i++) {
		ThreadInfo *cursor = readyThreads[i];
		if (cursor == NULL)
			continue;
		cursor->relaxation_ticks = (cursor->max_ticks) - (cursor->estimated_ticks - cursor->execution_ticks + (ticks -  cursor->start_ticks));
		if (cursor->relaxation_ticks < 0)
			cursor->relaxation_ticks = 0;
		cursor->dynamic_priority = 50 - (100 - (cursor->relaxation_ticks * 100 / (cursor->max_ticks - cursor->estimated_ticks)));
		if (cursor->dynamic_priority < -50)
			cursor->dynamic_priority = -50;
	}
}

void ganttHeader() {
	char buffer[200];
	sprintf(buffer, "gantt\n\r\ttitle Gantt Scheduler Diagram\n\r\t\tdateFormat x\n\r\t\tsection Execution\n\r");
	send(buffer, strlen(buffer));
}

void ganttLine(char taskName, int start_ticks, int end_ticks) {
	char buffer[200];
	osTimerStop(timer_id);
	sprintf(buffer, "\t\t%c\t:t, %d, %d\n\r", taskName, start_ticks, end_ticks);
	send(buffer, strlen(buffer));
	osTimerStart(timer_id, TIMER);
}
