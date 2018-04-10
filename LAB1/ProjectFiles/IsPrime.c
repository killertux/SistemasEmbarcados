#include "cmsis_os.h"
#include "Flags.h"
#include "IsPrime.h"
#include <math.h>

osThreadId tid_Is_Prime;                            // thread id
osThreadDef (is_prime, osPriorityNormal, 1, 0);

int init_isPrime() {
    tid_Is_Prime = osThreadCreate(osThread(is_prime), NULL);
    if (!tid_Is_Prime) return (-1);
    return 0;
}

void is_prime() {
    uint32_t endPoint = (uint32_t) sqrt(key);
    uint32_t i = 3;
    bool prime;

    while (1) {
        // Awaits until there is a new key to be tested as prime
        while (!f_prime) {
            osThreadYield();
        }

        f_prime = false;
        prime = true;
        // Checks every number for plain division, until the input's square root
        for (i = 3; i < endPoint; i += 2) {
            if (key % i == 0) {
                prime = false;
                f_generate = true;
                osThreadYield();
                break;
            }
        }

        // Sets the decode flag
        if (prime)
            f_decode = true;
        osThreadYield();
    }
}
