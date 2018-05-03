#include "cmsis_os.h"
#include "Adversaries.h"

osThreadId tid_adversaries;                            // thread id
osThreadDef (adversaries, osPriorityNormal, 1, 0);

int init_adversaries() {
    tid_adversaries = osThreadCreate(osThread(adversaries), NULL);
    if (!tid_adversaries) return (-1);
    return 0;
}

void adversaries() {

}
