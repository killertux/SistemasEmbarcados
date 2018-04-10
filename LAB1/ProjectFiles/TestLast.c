#include "TestLast.h"
#include "cmsis_os.h"
#include "Flags.h"
#include "stdlib.h"
#include "utils.h"

osThreadId tid_last;                            // thread id
osThreadDef (test_last, osPriorityNormal, 1, 0);

int init_test_last() {
    tid_last = osThreadCreate(osThread(test_last), NULL);
    if (!tid_last) return (-1);
    return 0;
}

void test_last() {
    uint32_t last_word;
    while (1) {
        // Check the flag defined by decode thread.
        while (!f_test_last) {
            osThreadYield();
        }
        f_test_last = false;
        last_word = getWord(msg + 34 * 4) + key;

        // Several operations, used to show parallel behavior at GANTT diagram.
#ifdef GANTT
        {
            int i = 0;
            for(i = 0 ; i < 50000; i++);
        }
#endif

        // Last word test
        if (((key * key) / last_key) == last_word) {
            passed_last = true;
        } else {
            passed_last = false;
        }

        // Stores the last key to use on the next testLast execution
        last_key = key;

        // Sets its finished flag
        f_finished_test_last = true;
        osThreadYield();
    }
}