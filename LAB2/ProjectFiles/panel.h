#ifndef PANEL_H
#define PANEL_H

#include <stdint.h>
#include <stdio.h>
#include "Display.h"

void panel_draw(Display *display, int meter, int score, int panel_car_color, int day);

#endif