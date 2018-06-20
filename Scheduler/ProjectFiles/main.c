#include "cmsis_os.h"
#include "TM4C129.h"

#include "DisplayUtils.h"
#include "DisplayThread.h"
#include "Threads.h"
#include "Scheduler.h"

int main() {
	osKernelInitialize();
	
	initDisplay();
	initDisplayThread();
	initThreads();
	initScheduler();
	
	osKernelStart();
	scheduler();
}
