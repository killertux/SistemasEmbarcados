#ifndef UART_SEND_H
#define UART_SEND_H
#include "cmsis_os.h"

typedef struct {                                                
  char *screen[30];
	char name[30];
	int position;
	int size;
} MAILQUEUE_OBJ_t;

void UART_send();
osThreadId init_UART_send(osMailQId UART_send_id);

#endif
