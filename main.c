/*
 * main.c
 *
 *  Created on: Feb 12, 2023
 *
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "TIMERS_interface.h"
#include "TIMERS_config.h"
#include "TIMERS_private.h"
#include "EXTI_interface.h"
#include "GI_interface.h"
#include "DC_motor.h"
#include "LCD.h"

#define F_CPU 16000000UL
#include <util/delay.h>

void ult_int1(void);
u8 sensor_on_flag=0 , rising_edge_flag=0 ;
u16 counter_ovf=0 , distance=50;

int main(void)
{
	u16 dist_left=0 , dist_right=0;
	DIO_voidInit();
	//DIO_u8SetPinDirection(DIO_u8_PORTD, DIO_u8_PIN5, DIO_u8_OUTPUT); servo pin
	ultrasonic_INIT();
	LCD_INIT();
	DC_MOTOR_INIT(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN5,DIO_u8_PORTB,DIO_u8_PIN3,0);
	DC_MOTOR_INIT(DIO_u8_PORTB,DIO_u8_PIN6,DIO_u8_PIN7,DIO_u8_PORTB,DIO_u8_PIN3,0);
	GI_voidEnbale();
	TIMERS_voidTIMERSInit();
	EXTI_u8SetCallBack(EXTI_u8_INT1 , &ult_int1);
	EXTI_u8EXTIEnabele(EXTI_u8_INT1 , EXTI_u8_ANY_LOGICAL_CHANGE_EDGE);
	TIMER_timer1SetCompareMatchAValue(330);
	_delay_ms(100);

	if(sensor_on_flag==0)
		{
			ultrasonic_triger();
			sensor_on_flag=1;
		}
	_delay_ms(100);


	while(1)
	{



         	if(distance<35)
		{
			DC_MOTOR_STOP(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN5,155); //left wheels
			DC_MOTOR_STOP(DIO_u8_PORTB,DIO_u8_PIN6,DIO_u8_PIN7,155); //right wheels
			LCD_WRITE_COMMAND(clear_lcd);
			LCD_WRITE_STRING("stop");

			_delay_ms(100);
			DC_MOTOR_BACKWARD(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN5,155); //left wheels
			DC_MOTOR_BACKWARD(DIO_u8_PORTB,DIO_u8_PIN6,DIO_u8_PIN7,155); //right wheels
			LCD_WRITE_COMMAND(clear_lcd);
			LCD_WRITE_STRING("BackWard");

			_delay_ms(500);

			DC_MOTOR_STOP(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN5,155); //left wheels
			DC_MOTOR_STOP(DIO_u8_PORTB,DIO_u8_PIN6,DIO_u8_PIN7,155); //right wheels
			LCD_WRITE_COMMAND(clear_lcd);
			LCD_WRITE_STRING("stop");




			TIMER_timer1SetCompareMatchAValue(120);
			dist_left=distance;
			_delay_ms(700);




			TIMER_timer1SetCompareMatchAValue(500);
			dist_right=distance;
			_delay_ms(700);



			TIMER_timer1SetCompareMatchAValue(330);

			if(dist_left>dist_right)
			{
				DC_MOTOR_STOP(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN5,80); //left wheels
				DC_MOTOR_FORWARD(DIO_u8_PORTB,DIO_u8_PIN6,DIO_u8_PIN7,200); //right wheels
				LCD_WRITE_COMMAND(clear_lcd);
				LCD_WRITE_STRING("left");
				_delay_ms(700);
				DC_MOTOR_STOP(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN5,80); //left wheels
				DC_MOTOR_STOP(DIO_u8_PORTB,DIO_u8_PIN6,DIO_u8_PIN7,80); //right wheels
				LCD_WRITE_COMMAND(clear_lcd);
				LCD_WRITE_STRING("stop");
				_delay_ms(700);
			}


			else
			{
				DC_MOTOR_FORWARD(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN5,200); //left wheels
				DC_MOTOR_STOP(DIO_u8_PORTB,DIO_u8_PIN6,DIO_u8_PIN7,155); //right wheels
				LCD_WRITE_COMMAND(clear_lcd);
				LCD_WRITE_STRING("right");
				_delay_ms(700);


				DC_MOTOR_STOP(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN5,155); //left wheels
				DC_MOTOR_STOP(DIO_u8_PORTB,DIO_u8_PIN6,DIO_u8_PIN7,155); //right wheels
				LCD_WRITE_COMMAND(clear_lcd);
				LCD_WRITE_STRING("stop");
				_delay_ms(700);
			}

		}

		else
		{
			if(distance >300)
			{
			DC_MOTOR_FORWARD(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN5,255); //left wheels
			DC_MOTOR_FORWARD(DIO_u8_PORTB,DIO_u8_PIN6,DIO_u8_PIN7,255); //right wheels
			LCD_WRITE_COMMAND(clear_lcd);

			}
			else if((distance>150)&&(distance>=300))
			{
				DC_MOTOR_FORWARD(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN5,155); //left wheels
				DC_MOTOR_FORWARD(DIO_u8_PORTB,DIO_u8_PIN6,DIO_u8_PIN7,155); //right wheels
				LCD_WRITE_COMMAND(clear_lcd);

			}
			else
			{
				DC_MOTOR_FORWARD(DIO_u8_PORTB,DIO_u8_PIN4,DIO_u8_PIN5,80); //left wheels
				DC_MOTOR_FORWARD(DIO_u8_PORTB,DIO_u8_PIN6,DIO_u8_PIN7,80); //right wheels
				LCD_WRITE_COMMAND(clear_lcd);

			}

			LCD_WRITE_STRING("Forward");
		}
		if(sensor_on_flag==0)
					{
							ultrasonic_triger();
							sensor_on_flag=1;

					}

		}


	return 0;
}

void ult_int1(void)
{
	if(sensor_on_flag==1)
	{
	if(rising_edge_flag==0)
	{
		counter_ovf=0;
		TIMERS_u8_TCNT2_REG=0;
		rising_edge_flag=1;
	}
	else
	{
		distance=((counter_ovf*256)+TIMERS_u8_TCNT2_REG)*0.0686 ;
		/*if(distance<400)
			{
				LCD_vidGotoxy(2,1);
				LCD_WRITE_COMMAND(clear_lcd);
				LCD_vidWriteNumber(distance);

			}*/
		counter_ovf=0;
		TIMERS_u8_TCNT2_REG=0;
		rising_edge_flag=0;
		sensor_on_flag=0;
	}
	}
}
void __vector_5(void)       __attribute__((signal));
void __vector_5(void)
{
	counter_ovf++;

}

