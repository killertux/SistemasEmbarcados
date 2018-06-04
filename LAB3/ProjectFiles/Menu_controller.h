#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

// object data type
typedef struct {                                                
  osMessageQId menu_controller_msg_queue_id;
  osMessageQId green_led_msg_id;
	osMessageQId blue_led_msg_id;
	osMessageQId red_led_msg_id;
	osMailQId UART_send_id;
} MENU_CONTROLLER_IDS;

typedef struct {
	char name[30];
	int size;
	unsigned int *codes;
	char *names[20];
} ColorGroup;

typedef struct {
	int colorGroupPosition;
	int colorPosition;
	ColorGroup groups[9];
} Menu;


void menu_controller();

osThreadId init_menu_controller(osMessageQId menu_controller_msg_queue_id,
											osMessageQId red_led_msg_id,
											osMessageQId green_led_msg_id,
											osMessageQId blue_led_msg_id,
											osMailQId UART_send_id);

void uart_send(osMailQId UART_send_id);
void draw_menu();
void clearScreen();
void sendMessages();

#endif