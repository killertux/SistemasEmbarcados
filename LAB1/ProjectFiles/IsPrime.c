#include "cmsis_os.h"
#include "Flags.h"
#include "IsPrime.h"
#include "stdbool.h"
#include <math.h>

osThreadId tid_Is_Prime;                            // thread id
osThreadDef (is_prime, osPriorityNormal, 1, 0);

int init_isPrime()
{
	tid_Is_Prime = osThreadCreate (osThread(is_prime), NULL);
  if (!tid_Is_Prime) return(-1);
	return 0;
}

void is_prime()
{
		int endPoint = (int) sqrt(key);
	  int i = 3;
	
		while(1) {
		     while (!prime_await) {
		 
		}
		 

     for(i = 3; i < endPoint; i+= 2) {
         if (key % i == 0) {
					 prime = false;
           prime_await = false;
				 }
     }
		 
		 prime = true;
     prime_await = false;
	 }
}
