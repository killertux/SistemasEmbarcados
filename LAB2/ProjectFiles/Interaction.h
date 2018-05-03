#ifndef INTERACTION_H
#define INTERACTION_H

#include "Information.h"

extern osThreadId tid_interaction; 

void interaction(Information *info);

int init_interaction(Information *info);

#endif
