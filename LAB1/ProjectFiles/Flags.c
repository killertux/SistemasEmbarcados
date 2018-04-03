#ifndef FLAGS_H
#define FLAGS_H

#include "stdbool.h"
#include "Flags.h"

unsigned char generated;
unsigned char prime;
unsigned char prime_await;
unsigned char finished_decoding;
unsigned char passed_last;
unsigned char passed_last_await;
unsigned char passed_penultimate ;
unsigned passed_penultimate_await ;
int key;

void init_flags() {
	generated = 0;
	prime = 0;
	prime_await = 0;
	finished_decoding = 0;
	passed_last = 0;
	passed_last_await = 1;
	passed_penultimate = 0;
	passed_penultimate_await = 1;
}

#endif
