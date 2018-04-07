#include "Decode.h"
#include "cmsis_os.h"
#include "Flags.h"
#include "msg1.h"
#include "msg2.h"
#include "msg3.h"

osThreadId tid_Decode;                            // thread id
osThreadDef (decode, osPriorityNormal, 1, 0);

int init_decode()
{
	tid_Decode = osThreadCreate (osThread(decode), NULL);
  if (!tid_Decode) return(-1);
	return 0;
}

void decode()
{
	unsigned char *msg = msg1_bin;
	unsigned int len  = msg1_bin_len;
	while(1) {
		if(prime == 1 && prime_await == 0) {
			for(len =0; len < 100; len++) {
				int a = 0;
				a++;
				msg[1] = 'l';
			}
			finished_decoding = 3;
			passed_last_await =1;
			passed_penultimate_await =1;
			osThreadYield();
		}
	}
}