#ifndef BLINK_CAR_INSTRUMENT_H
#define BLINK_CAR_INSTRUMENT_H


static void Timer2_Callback (void const *arg);    // prototype for timer 
                                                  //  callback function
static osTimerId id2;                             // timer id
static uint32_t  exec2;                           // argument for the 
                                                  //  timer call back 
                                                  //  function
static osTimerDef (Timer2, Timer2_Callback);

#endif