#include "cmsis_os.h"
#include "Instruments.h"

osThreadId tid_instruments;                            // thread id
osThreadDef (instruments, osPriorityNormal, 1, 0);

int init_instruments() {
    tid_instruments = osThreadCreate(osThread(instruments), NULL);
    if (!tid_instruments) return (-1);
    return 0;
}

void instruments() {
}
