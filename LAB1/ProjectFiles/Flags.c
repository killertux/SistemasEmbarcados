#include "stdbool.h"
#include "Flags.h"
#include "stdint.h"
#include "grlib/grlib.h"

#include "msg1.h"
#include "msg2.h"
#include "msg3.h"
#include "msg4.h"
#include "msg5.h"

bool f_generate;
bool f_prime;
bool f_decode;
bool f_test_last;
bool f_test_penultimate;
bool f_finished_test_last;
bool f_finished_test_penultimate;
bool f_end;
bool passed_last;
bool passed_penultimate ;
uint32_t key;
uint32_t last_key;
uint32_t tick;
unsigned char decoded_msg[35];
unsigned char *msg;
tContext sContext;

void init_flags() {
	f_generate = true;
	f_prime = false;
	f_decode = false;
	f_test_last = false;
	f_test_penultimate = false;
	f_finished_test_last = false;
	f_finished_test_penultimate = false;
	f_end = false;
	passed_last = false;
	passed_penultimate = false;
	last_key = 0;
	key = 0;
	#ifdef MSG1
	msg = msg1_bin;
	#endif
	#ifdef	MSG2
	msg = msg2_bin;
	#endif
	#ifdef MSG3
	msg = msg3_bin;
	#endif
	#ifdef MSG4
	msg = msg4_bin;
	#endif
	#ifdef MSG5
	msg = msg5_bin;
	#endif
}
