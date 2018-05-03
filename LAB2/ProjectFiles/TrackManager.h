#ifndef TRACK_MANAGER_H
#define TRACK_MANAGER_H

#include "Information.h"

extern osThreadId tid_trackmanager;  

int init_track_manager(Information *info);

void track_manager(Information *info);

#endif
