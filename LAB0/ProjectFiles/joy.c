//..............................................................................
// joy.c - Driver for the Joystick.
//
// Copyright (c) 2017 
// Allan Patrick de Souza - <allansouza@alunos.utfpr.edu.br>
// Guilherme Jacichen     - <jacichen@alunos.utfpr.edu.br>
// Jessica Isoton Sampaio - <jessicasampaio@alunos.utfpr.edu.br>
// Mariana Carri�o        - <mcarriao@alunos.utfpr.edu.br>
//
// All rights reserved. 
// Software License Agreement
//...............................................................................

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "grlib/grlib.h"

#include "joy.h"

/***************************************************************************//**
 * @brief set the peripheral ADC0, the peripheral GPIOE and the peripheral GPIOC
 ******************************************************************************/
void joy_init(void){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	
	// Enable the GPIOC peripheral
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	
	// Wait for the GPIOC module to be ready.
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC));

	// Initialize the GPIO pin configuration.
	// Set pins as input, SW controlled.
	GPIOPinTypeGPIOInput(GPIO_PORTC_BASE,GPIO_PIN_6); // Joystick Z

}

/***************************************************************************//**
 * @brief Read the analog value from ADC0 and return a uint16_t(voltage value).
 * @param  port is the port used to access the desired pin.
 * @param  pin to be read through ADC channel.
 * @param  channel to be read to get the value from the pin.
 * @return result[0] the voltage value corresponded to the channel.
 ******************************************************************************/
static uint16_t analog_read(uint32_t port, uint8_t pin, uint32_t channel)
{
	uint32_t result[1];

	ADCSequenceStepConfigure(ADC0_BASE, 3, 0, channel | ADC_CTL_IE | ADC_CTL_END);
	GPIOPinTypeADC(port, pin);
	ADCSequenceConfigure(ADC0_BASE, 3,  ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceEnable(ADC0_BASE, 3);
	ADCIntClear(ADC0_BASE, 3);
	// Trigger the ADC conversion.
	ADCProcessorTrigger(ADC0_BASE, 3);

	// Wait for conversion to be completed.
	while(!ADCIntStatus(ADC0_BASE, 3, false));
	
	// Clear the ADC interrupt flag.
	ADCIntClear(ADC0_BASE, 3);

	// Read ADC Value.
	ADCSequenceDataGet(ADC0_BASE, 3,  result);
	//ADCSequenceDisable(ADC0_BASE, 3);
 
	return result[0];
}

/***************************************************************************//**
 * @brief Read the pin that corresponds to the joystick center button. 
 * @return the bool value, false if the button was pressed, otherwise true
 ******************************************************************************/
bool joy_read_center(){
	return GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6) ? false : true;
}

/***************************************************************************//**
 * @brief Read the channel 9 that corresponds to the axis x
 * @return it is the corresponded voltage value from the axis x
 ******************************************************************************/
uint16_t joy_read_x(void){
	return analog_read(GPIO_PORTE_BASE, GPIO_PIN_4, ADC_CTL_CH9);			
}


/***************************************************************************//**
 * @brief Read the channel 0 that corresponds to the axis y
 * @return it is the corresponded voltage value from the axis y
 ******************************************************************************/
uint16_t joy_read_y(void){
	return analog_read(GPIO_PORTE_BASE, GPIO_PIN_3, ADC_CTL_CH0);			
}