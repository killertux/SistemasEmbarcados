#include "DisplayUtils.h"

tContext sContext;

void initDisplay() {
	cfaf128x128x16Init();
	GrContextInit(&sContext, &g_sCfaf128x128x16);
	GrContextFontSet(&sContext, g_psFontFixed6x8);
	GrContextBackgroundSet(&sContext, 0x000000);
	GrContextForegroundSet(&sContext, 0xffffff);
}

void print(char *msg, int line, int column) {
	GrStringDraw(&sContext, msg, -1, column * 7, line * 9, true);
}