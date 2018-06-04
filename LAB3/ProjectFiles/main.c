#include "cmsis_os.h"
#include "TM4C129.h"                    // Device header
#include <stdbool.h>
#include <stdio.h>
#include "grlib/grlib.h"
#include "UART_interrupt.h"
#include "UART_thread.h"
#include "Menu_controller.h"
#include <string.h>
#include "RGB.h"
#include "Red_led.h"
#include "Green_led.h"
#include "Blue_led.h"
#include "Uart_send.h"

#define MSGQUEUE_OBJECTS      16                       
#define MAILQUEUE_OBJECTS      16                               

//osMessageQId UART_msg_queue_id;                    
// message queue id
osMessageQDef (UART_MsgQueue, MSGQUEUE_OBJECTS, char); 
osMessageQId(UART_msg_queue_id);
// message queue object

osMessageQId menu_controller_msg_queue_id;                                  
// message queue id
osMessageQDef (menu_controller_MsgQueue, MSGQUEUE_OBJECTS, char); ; 
// message queue object

osMessageQId red_led_msg_queue_id;                                  
// message queue id
osMessageQDef (red_led_MsgQueue, MSGQUEUE_OBJECTS, char); 
// message queue object

osMessageQId blue_led_msg_queue_id;                               
// message queue id
osMessageQDef (blue_led_MsgQueue, MSGQUEUE_OBJECTS, char); 
// message queue object

osMessageQId green_led_msg_queue_id;                                  
// message queue id
osMessageQDef (green_led_MsgQueue, MSGQUEUE_OBJECTS, char); 
// message queue object

// Mail queue struct creation

// object data type

osMailQId UART_send_MailQueue_id;                                        
// mail queue id
osMailQDef (UART_send_MailQueue, MAILQUEUE_OBJECTS, MAILQUEUE_OBJ_t);     
// mail queue object

int main()
{
	osKernelInitialize();
	rgb_init();

	UART_msg_queue_id = osMessageCreate (osMessageQ(UART_MsgQueue), NULL);  
  menu_controller_msg_queue_id = osMessageCreate (osMessageQ(menu_controller_MsgQueue), NULL);  
  red_led_msg_queue_id = osMessageCreate (osMessageQ(red_led_MsgQueue), NULL);  
  blue_led_msg_queue_id = osMessageCreate (osMessageQ(blue_led_MsgQueue), NULL);  
	green_led_msg_queue_id = osMessageCreate (osMessageQ(green_led_MsgQueue), NULL);  
  UART_send_MailQueue_id = osMailCreate (osMailQ(UART_send_MailQueue), NULL); 
	
	init_uart(UART_msg_queue_id);
	init_UART_thread(menu_controller_msg_queue_id, &UART_msg_queue_id);
	init_menu_controller(menu_controller_msg_queue_id, red_led_msg_queue_id, green_led_msg_queue_id, blue_led_msg_queue_id, UART_send_MailQueue_id);
	init_red_led(red_led_msg_queue_id);
	init_blue_led(blue_led_msg_queue_id);
	init_green_led(green_led_msg_queue_id);
	init_UART_send(UART_send_MailQueue_id);
	
	osKernelStart(); 

	osDelay(osWaitForever);
}
