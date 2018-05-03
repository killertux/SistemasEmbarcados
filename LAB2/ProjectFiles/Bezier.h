#ifndef BEZIER_H
#define BEZIER_H

#include "Display.h"

void draw_bezier_curve(Display *display, float displacement, uint32_t color, float x1, float y1, float x2, float y2, float x3, float y3);
float bezier_curve_car(float displacement, float x1, float y1, float x2, float y2, float x3, float y3, float car_y);

#endif