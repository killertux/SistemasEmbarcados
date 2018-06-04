#include "cmsis_os.h"
#include "Blue_led.h"
#include "RGB.h"

osThreadDef (blue_led, osPriorityNormal, 1, 0);

osThreadId init_blue_led(osMessageQId blue_led_msg_id) {
		osThreadId tid_blue_led; 
    tid_blue_led = osThreadCreate(osThread(blue_led), blue_led_msg_id);
    if (!tid_blue_led) return (osThreadId) (-1);
    return tid_blue_led;
}

void blue_led(osMessageQId blue_led_msg_id) {
	osStatus status;
	osEvent evt;
	char msg;
 
  while (1) {
    evt = osMessageGet (blue_led_msg_id, osWaitForever); 
    // wait for message
 
    if (evt.status == osEventMessage) {
      msg = evt.value.v;
			rgb_write_b(msg);
    }
  }
}