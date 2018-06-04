#include "cmsis_os.h"
#include "UART_interrupt.h"

char bla;

osMessageQId ti_UART_msg_queue_id;
void UART0_Handler() {
	char msg;
	msg = *UART0DR;
	bla = msg;
	osMessagePut(ti_UART_msg_queue_id, msg, 0);
}

void init_uart(osMessageQId p_UART_msg_queue_id) {
   ti_UART_msg_queue_id = p_UART_msg_queue_id;
	//Enables the UART0 module
	*RCGCUART |= 0x01;
	
	//Enables the clock to the GPIO module PORT A
	*RCGCGPIO |= 0x01;
	
	//Configure the GPIO pin to work as UART and SSI
	*GPIOFSEL_A = (1 << 0) | (1 << 1);
	
	//Enables the Port Mux to the UART as specified by table 23-5 of datasheet (PMC0 PMC1)
	*GPIOPCTL_A = (1 << 0) | (1 << 4);
	
	//Sets port to Digital Mode
	*GPIODEN_A = (1 << 0) | (1 << 1);
	
	//Enables the UART0 Receive interrupt
	*UART0IM = (1<<4);
	//Enables UART0 Interrupt at EN0
	*EN0 |= (1<<5); 
	
	//Let's disable the UART0 so we can configure the baud-rate
	*UART0CTL &= ~(1 << 0);
	
	//We need to calculate the baud-rate divisor (BRD)
	//BRD = 120.000.000 / (16 * 9600) = 781.25
	//Now, we need to separete the integer part (781) and calculate the fractional part (0.25)
	//UARTFBRD[DIVFRAC] = integer(0.25 * 64 + 0.5) = 16
	//We should configure the UART to use these values
	*UART0IBRD = 781;
	*UART0FBRD = 16;
	
	
	/*//We need to calculate the baud-rate divisor (BRD)
	//BRD = 16.000.000 / (16 * 9600) = 104.1666
	//Now, we need to separete the integer part (781) and calculate the fractional part (0.25)
	//UARTFBRD[DIVFRAC] = integer(0.16667 * 64 + 0.5) = 11
	//We should configure the UART to use these values
	*UART0IBRD = 104;
	*UART0FBRD = 11;*/
	
	//Configure UART to use 8 bits, not use parity end just 1 stop bit
	*UART0LCRH = (1 << 5) | (1 << 6);
	
	//Set UART Clock Source to system clock
	*UART0CC = 0x0;
	
	//Finally, let's enable the UART
	*UART0CTL = (1<<0) | (1 << 8) | (1 << 9);
}

void send_byte(char data) {
	while ((*UART0FF & (1<<5)) != 0);
	*UART0DR = data;
}

void send(char *data, int n_bytes) {
	int i;
	for(i = 0; i < n_bytes; i++)
		send_byte(data[i]);
}