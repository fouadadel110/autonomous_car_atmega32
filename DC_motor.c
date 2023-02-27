/*
SWC  :DC_motor
DATE :12/2/2023
*/

/*include LIB layer*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"

#include "TIMERS_interface.h"
#include "TIMERS_private.h"
#include "TIMERS_config.h"

void DC_MOTOR_INIT(u8 Copy_u8PortId, u8 Copy_u8PinId_1,u8 Copy_u8PinId_2,u8 Copy_u8_PWM_PORT,u8 Copy_u8_PWM_PIN,u8 Copy_u8_duty)
{
  DIO_u8SetPinDirection ( Copy_u8PortId,  Copy_u8PinId_1 ,DIO_u8_OUTPUT);
  DIO_u8SetPinDirection ( Copy_u8PortId,  Copy_u8PinId_2 ,DIO_u8_OUTPUT);
  DIO_u8SetPinDirection ( Copy_u8_PWM_PORT,  Copy_u8_PWM_PIN ,DIO_u8_OUTPUT);


  DIO_u8SetPinValue( Copy_u8PortId,  Copy_u8PinId_1 ,DIO_u8_LOW );
  DIO_u8SetPinValue( Copy_u8PortId,  Copy_u8PinId_2 ,DIO_u8_LOW );

  TIMERS_timer0SetCompareMatchValue(Copy_u8_duty);

}
void DC_MOTOR_FORWARD(u8 Copy_u8PortId, u8 Copy_u8PinId_1,u8 Copy_u8PinId_2,u8 Copy_u8_duty)
{
  DIO_u8SetPinValue( Copy_u8PortId,  Copy_u8PinId_1 ,DIO_u8_HIGH );
  DIO_u8SetPinValue( Copy_u8PortId,  Copy_u8PinId_2 ,DIO_u8_LOW );

  TIMERS_timer0SetCompareMatchValue(Copy_u8_duty);
}
void DC_MOTOR_BACKWARD(u8 Copy_u8PortId, u8 Copy_u8PinId_1,u8 Copy_u8PinId_2,u8 Copy_u8_duty)
{
  DIO_u8SetPinValue( Copy_u8PortId,  Copy_u8PinId_1 ,DIO_u8_LOW );
  DIO_u8SetPinValue( Copy_u8PortId,  Copy_u8PinId_2 ,DIO_u8_HIGH );

  TIMERS_timer0SetCompareMatchValue(Copy_u8_duty);

}
void DC_MOTOR_STOP(u8 Copy_u8PortId, u8 Copy_u8PinId_1,u8 Copy_u8PinId_2,u8 Copy_u8_duty)
{
  DIO_u8SetPinValue( Copy_u8PortId,  Copy_u8PinId_1 ,DIO_u8_LOW );
  DIO_u8SetPinValue( Copy_u8PortId,  Copy_u8PinId_2 ,DIO_u8_LOW );

  TIMERS_timer0SetCompareMatchValue(Copy_u8_duty);
}
