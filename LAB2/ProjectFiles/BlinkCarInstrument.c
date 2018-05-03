#include "cmsis_os.h"                                           
#include "BlinkCarInstrument.h"

void Init_Timers (void) {
  osStatus status;                                // function return 
                                                  //  status
 
	/*
  // Create one-shoot timer
  exec1 = 1;
  id1 = osTimerCreate (osTimer(Timer1), osTimerOnce, &exec1);
  if (id1 != NULL) {    // One-shot timer created
    // start timer with delay 100ms
    status = osTimerStart (id1, 100);            
    if (status != osOK) {
      // Timer could not be started
    }
	}*/
 
  // Create periodic timer
  exec2 = 2;
  id2 = osTimerCreate (osTimer(Timer2), osTimerPeriodic, &exec2);
  if (id2 != NULL) {    // Periodic timer created
    // start timer with periodic 1000ms interval
    status = osTimerStart (id2, 1000);            
    if (status != osOK) {
      // Timer could not be started
    }
  }
}