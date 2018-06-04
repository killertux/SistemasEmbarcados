#ifndef GREEN_LED_H
#define GREEN_LED_H

void green_led(osMessageQId green_led_msg_id);
osThreadId init_green_led(osMessageQId green_led_msg_id);

#endif