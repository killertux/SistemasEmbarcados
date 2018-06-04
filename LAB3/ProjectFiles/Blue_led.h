#ifndef BLUE_LED_H
#define BLUE_LED_H

void blue_led(osMessageQId blue_led_msg_id);
osThreadId init_blue_led(osMessageQId blue_led_msg_id);

#endif