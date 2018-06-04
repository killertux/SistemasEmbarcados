#ifndef UART_THREAD_H
#define UART_THREAD_H
#include "cmsis_os.h"

void UART_thread();
osThreadId init_UART_thread(osMessageQId p_menu_controller_msg_queue_id, osMessageQId *p_UART_msg_queue_id);

#endif