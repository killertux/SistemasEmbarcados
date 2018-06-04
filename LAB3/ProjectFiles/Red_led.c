#include "cmsis_os.h"
#include "Red_led.h"
#include "RGB.h"

osThreadDef (red_led, osPriorityNormal, 1, 0);

osThreadId init_red_led(osMessageQId red_led_msg_id) {
		osThreadId tid_red_led; 
    tid_red_led = osThreadCreate(osThread(red_led), red_led_msg_id);
    if (!tid_red_led) return (osThreadId) (-1);
    return tid_red_led;
}

void red_led(osMessageQId red_led_msg_id) {
	osStatus status;
	osEvent evt;
	char msg;
 
  while (1) {
    evt = osMessageGet (red_led_msg_id, osWaitForever); 
    // wait for message
 
    if (evt.status == osEventMessage) {
      msg = evt.value.v;
			rgb_write_r(msg);
    }
  }
}