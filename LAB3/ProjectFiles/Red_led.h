#ifndef RED_LED_H
#define RED_LED_H

void red_led(osMessageQId red_led_msg_id);
osThreadId init_red_led(osMessageQId red_led_msg_id);

#endif