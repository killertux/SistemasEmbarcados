#ifndef DISPLAY_UTILS_H
#define DISPLAY_UTILS_H

#include <stdbool.h>
#include <stdint.h>
#include "grlib/grlib.h"
#include "cfaf128x128x16.h"
#include "string.h"
#include "stdio.h"

extern tContext sContext;

void initDisplay(void);
void print(char *msg, int line, int column);

#endif
