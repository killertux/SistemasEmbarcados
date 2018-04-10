#ifndef FLAGS_H
#define FLAGS_H
#include <stdint.h>
#include <stdbool.h>
#include "grlib/grlib.h"

#define MSG4
#define DEBUG
//#define GANTT

void init_flags();

extern bool f_generate;
extern bool f_prime;
extern bool f_decode;
extern bool f_test_last;
extern bool f_test_penultimate;
extern bool f_finished_test_last;
extern bool f_finished_test_penultimate;
extern bool f_end;
extern bool passed_last;
extern bool passed_penultimate;
extern uint32_t key;
extern uint32_t last_key;
extern tContext sContext;
extern uint32_t tick;

extern unsigned char *msg;
extern unsigned char decoded_msg[35];

#endif
