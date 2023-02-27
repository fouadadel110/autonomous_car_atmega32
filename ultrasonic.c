/*
 * ultrasonic.c
 *
 *  Created on: Feb 18, 2023
 *
 */
#include "DIO_config.h"
#include "DIO_interface.h"
#include "util/delay.h"

void ultrasonic_INIT(void)
{
	DIO_u8SetPinDirection(DIO_u8_PORTD,DIO_u8_PIN2,DIO_u8_PORT_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8_PORTD,DIO_u8_PIN3,DIO_u8_PORT_INPUT);
	DIO_u8SetPinValue(DIO_u8_PORTD,DIO_u8_PIN3,DIO_u8_HIGH);
}
void ultrasonic_triger(void)
{
	DIO_u8SetPinValue(DIO_u8_PORTD,DIO_u8_PIN2,DIO_u8_HIGH);
	_delay_us(15);
	DIO_u8SetPinValue(DIO_u8_PORTD,DIO_u8_PIN2,DIO_u8_LOW);
}
