#include "cmsis_os.h"
#include "UART_thread.h"
#include "UART_interrupt.h"

osThreadDef (UART_thread, osPriorityNormal, 1, 0);

osMessageQId t_menu_controller_msg_queue_id;
osMessageQId *t_UART_msg_queue_id;

osThreadId init_UART_thread(osMessageQId p_menu_controller_msg_queue_id, osMessageQId *p_UART_msg_queue_id) {
		osThreadId tid_UART_thread; 	
		t_menu_controller_msg_queue_id = p_menu_controller_msg_queue_id;
		t_UART_msg_queue_id = p_UART_msg_queue_id;
    tid_UART_thread = osThreadCreate(osThread(UART_thread), NULL);
    if (!tid_UART_thread) return (osThreadId) (-1);
    return tid_UART_thread;
}

void UART_thread() {
	osStatus status;
	osEvent evt;
	char msg;
	while(1) {
		evt = osMessageGet (*t_UART_msg_queue_id, osWaitForever);
		if(evt.status == osEventMessage) {
			msg = evt.value.v;
			osMessagePut(t_menu_controller_msg_queue_id, msg, osWaitForever);
		}
	}
}