#include "Display.h"
#include "cfaf128x128x16.h"

void display_init(Display *display) {
	int x,y;
	cfaf128x128x16Init();
	GrContextInit(&display->sContext, &g_sCfaf128x128x16);
	GrFlush(&display->sContext);
	for(x = 0; x < 128; x++)
		for(y = 0; y < 128; y++){
			display->back_buffer[x][y] = 0x0;
			display->front_buffer[x][y] = 0x0;
		}
}

void display_update(Display *display) {
	int x,y;
	for(x = 0; x < 128; x++)
		for(y = 0; y < 128; y++)
			if(display->back_buffer[x][y] != display->front_buffer[x][y]) {
				display->front_buffer[x][y] = display->back_buffer[x][y];
				GrContextForegroundSet(&display->sContext, display->front_buffer[x][y]);
				GrPixelDraw(&display->sContext, x, y);
			}
}

void display_clear_back_buffer(Display *display) {
	int x,y;
	for(x = 0; x < 128; x++)
		for(y = 0; y < 128; y++)
			display->back_buffer[x][y] = 0x0;
}