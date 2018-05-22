#include "UART.h"

void init_uart() {
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
	//Let's disable the UART0 so we can configure the baud-rate
	*UART0CTL = ~(1 << 0);
	//We need to calculate the baud-rate divisor (BRD)
	//BRD = 120.000.000 / (16 * 9600) = 781.25
	//Now, we need to separete the integer part (781) and calculate the fractional part (0.25)
	//UARTFBRD[DIVFRAC] = integer(0.25 * 64 + 0.5) = 16
	//We should configure the UART to use these values
	*UART0IBRD = 781;
	*UART0FBRD = 16;
	//Configure UART to use 8 bits, not use parity end just 1 stop bit
	*UART0LCRH = (1 << 5) | (1 << 6);
	//Set UART Clock Source to system clock
	*UART0CC = 0x0;
	//Finaly, let's enable the UART
	*UART0CTL = (1<<0) | (1 << 8) | (1 << 9);
}

void send_byte(void *data) {
	while((*UART0FF & (1<<5)) != 0);
	*UART0DR = (uint32_t)(char)data;
}

void send_char(char c) {
	while((*UART0FF & (1<<5)) != 0);
	*UART0DR = (uint32_t)c;
}