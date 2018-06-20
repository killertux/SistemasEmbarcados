#ifndef DISPLAY_THREAD_H
#define DISPLAY_THREAD_H

#include <cmsis_os.h>
#include "Threads.h"
#include "DisplayUtils.h"

void initDisplayThread();
void display();

#endif
