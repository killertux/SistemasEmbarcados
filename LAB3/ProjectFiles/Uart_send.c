#include "cmsis_os.h"
#include "Red_led.h"
#include "RGB.h"
#include "Uart_send.h"
#include "Uart_interrupt.h"
#include <string.h>

osThreadDef (UART_send, osPriorityNormal, 1, 0);

osThreadId init_UART_send(osMailQId UART_send_msg_id) {
		osThreadId tid_UART_send; 
    tid_UART_send = osThreadCreate(osThread(UART_send), UART_send_msg_id);
    if (!tid_UART_send) return (osThreadId) (-1);
    return tid_UART_send;
}

void UART_send(osMailQId UART_send_msg_id) {
	osStatus status;
	osEvent evt;
	MAILQUEUE_OBJ_t  *pMail = 0;
	int i;
 
  while (1) {
    ; // Insert thread code here...
    evt = osMailGet (UART_send_msg_id, osWaitForever);             
    // wait for mail
 
    if (evt.status == osEventMail) {
      pMail = evt.value.p;
			
      // process data
			send_byte(0x0c);
			      
			send(pMail->name, strlen(pMail->name));
			send("\r\n", 2);
			send("\r\n", 2);
			
			for (i = 0; i < pMail->size; i++) {
				if(i == pMail->position)
					send_byte('*');
				send(pMail->screen[i], strlen(pMail->screen[i]));
				send("\r\n", 2);
			}
			
			// free memory allocated for mail
			osMailFree (UART_send_msg_id, pMail);
    }
  }
}