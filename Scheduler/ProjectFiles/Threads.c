#include "Threads.h"

#include "stdlib.h"

osThreadDef (threadA, osPriorityIdle, 1, 0);
osThreadDef (threadB, osPriorityIdle, 1, 0);
osThreadDef (threadC, osPriorityIdle, 1, 0);
osThreadDef (threadD, osPriorityIdle, 1, 0);
osThreadDef (threadE, osPriorityIdle, 1, 0);
osThreadDef (threadF, osPriorityIdle, 1, 0);

ThreadInfo threads[6];

void initThreads(){
	threads[0].tid = osThreadCreate(osThread(threadA), NULL);
	threads[1].tid = osThreadCreate(osThread(threadB), NULL);
	threads[2].tid = osThreadCreate(osThread(threadC), NULL);
	threads[3].tid = osThreadCreate(osThread(threadD), NULL);
	threads[4].tid = osThreadCreate(osThread(threadE), NULL);
	threads[5].tid = osThreadCreate(osThread(threadF), NULL);
	
	/*initThreadInfo(&threads[0], 1278,  1.7, 10, 8);
	initThreadInfo(&threads[1], 526892, 1.5, 0, 2);
	initThreadInfo(&threads[2], 967, 1.3, -30, 5);
	initThreadInfo(&threads[3], 471, 1.5, 0, 1);
	initThreadInfo(&threads[4], 46843, 1.3, -30, 6);
	initThreadInfo(&threads[5], 4999603, 1.1, -100, 10);*/
	initThreadInfo(&threads[0], 84693, 1.7, 10, 8, 'A');
	initThreadInfo(&threads[1], 466892, 1.5, 0, 2, 'B');
	initThreadInfo(&threads[2], 15952, 1.3, -30, 5, 'C');
	initThreadInfo(&threads[3], 7199, 1.5, 0, 1, 'D');
	initThreadInfo(&threads[4], 78637, 1.3, -30, 6, 'E');
	initThreadInfo(&threads[5], 3059603, 1.1, -100, 10, 'F');
}

void initThreadInfo(ThreadInfo *thread, int estimated_ticks, float deadline, int static_priority, int frequency, char name) {
	thread->name = name;
	thread->estimated_ticks = estimated_ticks;
	thread->max_ticks = estimated_ticks * deadline;
	thread->static_priority = static_priority;
	thread->dynamic_priority = static_priority;
	thread->frequency = frequency;
	thread->master_fault = false;
	thread->secundary_fault = false;
	thread->running = false;
	thread->awaiting = true;
	thread->execution_ticks = 0;
	thread->start_ticks = 0;
	thread->await_time = 0;
	thread->aux_ticks = 0;
	thread->relaxation_ticks = 0;
}

void threadStart() {
	osSignalWait(0x01, osWaitForever);
}

void threadEnd(ThreadInfo *thread) {
	int ticks = osKernelSysTick();
	int time_alive = ticks - thread->start_ticks;
	bool too_slow = thread->max_ticks < (time_alive);
	bool too_fast = thread->estimated_ticks / 2 < (time_alive);
	thread->delay = time_alive - thread->execution_ticks;
	thread->awaiting = true;
	if (too_slow) {
		if (thread->static_priority == -100)
			thread->master_fault = true;
		else {
			thread->secundary_fault = true;
			thread->static_priority--;
		}
	} else if (too_fast && thread->static_priority != -100) {
		thread->static_priority++;
		thread->secundary_fault = true;
	}
	
	osSignalSet(scheduler_id, 0x01);
}
//1265
//1278
void threadA(){
	while (1) {
		threadStart();
		calculateThreadA(&threads[0].progress);
		threadEnd(&threads[0]);
	}
}

//132652
//526892
void threadB(){
	while (1) {
		threadStart();
		calculateThreadB(&threads[1].progress);
		threadEnd(&threads[1]);
	}
}

//958
//967
void threadC(){
	while (1) {
		threadStart();
		calculateThreadC(&threads[2].progress);
		threadEnd(&threads[2]);
	}
}

//449
//471
void threadD(){
	while (1) {
		threadStart();
		calculateThreadD(&threads[3].progress);
		threadEnd(&threads[3]);
	}
}

//44853
//46843
void threadE(){
	while (1) {
		threadStart();
		calculateThreadE(&threads[4].progress);
		threadEnd(&threads[4]);
	}
}

//2748221
//4999603
void threadF(){
	while (1) {
		threadStart();
		calculateThreadF(&threads[5].progress);
		threadEnd(&threads[5]);
	}
}
