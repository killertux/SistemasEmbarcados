#ifndef UART_INTERRUPT_H
#define UART_INTERRUPT_H
#include "cmsis_os.h"
#include "stdint.h"

#define RCGCUART 		((volatile uint32_t*) 0x400FE618)
#define RCGCGPIO 		((volatile uint32_t*) 0x400FE608)
	
//#define GPIOFSEL_A 	((volatile uint32_t*) 0x40004420)
#define GPIOFSEL_A 	((volatile uint32_t*) 0x40058420)
//#define GPIOPCTL_A 	((volatile uint32_t*) 0x4000452C)
#define GPIOPCTL_A 	((volatile uint32_t*) 0x4005852C)
//#define GPIODEN_A 	((volatile uint32_t*) 0x4000451C)
#define GPIODEN_A 	((volatile uint32_t*) 0x4005851C)

#define UART0CTL 		((volatile uint32_t*) 0x4000C030)
#define UART0IBRD		((volatile uint32_t*) 0x4000C024)
#define UART0FBRD		((volatile uint32_t*) 0x4000C028)
#define UART0LCRH		((volatile uint32_t*) 0x4000C02c)
#define UART0CC			((volatile uint32_t*) 0x4000CFC8)
#define UART0FF			((volatile uint32_t*) 0x4000C018)
#define UART0DR			((volatile uint32_t*) 0x4000C000)
#define UART0IM			((volatile uint32_t*) 0x4000C038)
	
#define EN0 				((volatile uint32_t*) 0xE000E100)


void init_uart();
void send_byte(char data);
void send(char *data, int n_bytes);
void read_byte();

extern osThreadId UART_Thread_id;
extern char bla;

#endif
