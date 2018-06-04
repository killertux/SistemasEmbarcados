#include "cmsis_os.h"
#include "Green_led.h"
#include "RGB.h"

osThreadDef (green_led, osPriorityNormal, 1, 0);

osThreadId init_green_led(osMessageQId green_led_msg_id) {
		osThreadId tid_green_led; 
    tid_green_led = osThreadCreate(osThread(green_led), green_led_msg_id);
    if (!tid_green_led) return (osThreadId) (-1);
    return tid_green_led;
}

void green_led(osMessageQId green_led_msg_id) {
	osStatus status;
	osEvent evt;
	char msg;
 
  while (1) {
    evt = osMessageGet (green_led_msg_id, osWaitForever); 
    // wait for message
 
    if (evt.status == osEventMessage) {
      msg = evt.value.v;
			rgb_write_g(msg);
    }
  }
}