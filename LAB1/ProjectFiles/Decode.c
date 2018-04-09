#include "Decode.h"
#include "cmsis_os.h"
#include "Flags.h"
#include "grlib/grlib.h"
#include "cfaf128x128x16.h"
#include "utils.h"

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
	int i;
	while(1) {
		while(!f_decode) {
			osThreadYield();
		}
		f_decode = false;
		
		for(i = 0; i < 35; i++) {
			uint32_t word = getWord(msg + i*4);
			decoded_msg[i] = (unsigned char)((i & 0x1) ? word + key : word - key);
		}
		
		f_test_last = true;
		f_test_penultimate = true;
		osThreadYield();
	}
}