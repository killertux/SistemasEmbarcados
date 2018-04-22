#ifndef DISPLAY_H
#define DISPLAY_H

#include "grlib/grlib.h"

typedef struct {
	tContext sContext;
	uint32_t front_buffer[128][128];
	uint32_t back_buffer[128][128];
} Display;

void display_init(Display *display);
void display_update(Display *display);
void display_clear_back_buffer(Display *display);

#endif