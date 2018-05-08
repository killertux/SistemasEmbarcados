#ifndef INTERACTION_H
#define INTERACTION_H

#include "Information.h"
#include "cmsis_os.h"

void interaction(Information *info);

osThreadId init_interaction(Information *info);

#endif
