#include "cmsis_os.h"
#include "EndCondition.h"

osThreadId tid_end_condition;                            // thread id
osThreadDef (end_condition, osPriorityNormal, 1, 0);

int init_end_condition() {
    tid_end_condition = osThreadCreate(osThread(end_condition), NULL);
    if (!tid_end_condition) return (-1);
    return 0;
}

void end_condition() {

}
