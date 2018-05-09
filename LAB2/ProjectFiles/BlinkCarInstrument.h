#ifndef BLINK_CAR_INSTRUMENT_H
#define BLINK_CAR_INSTRUMENT_H

#include "Information.h"
void Timer_Callback (const void *arg);
void create_timer (Information *info);
void start_timer();
void stop_timer();
void timer();
#endif