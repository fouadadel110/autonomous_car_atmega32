#define F_CPU 16000000UL
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "DIO_config.h"
#include"DIO_private.h"
#include "LCD.h"

void LCD_INIT()
{
	DIO_u8_DDRA_REG=0xFF;
	_delay_ms(20);
	CLR_BIT(DIO_u8_PORTA_REG,LCD_u8_E);
	_delay_ms(20);
	LCD_WRITE_COMMAND(0x02);		/* send for 4 bit initialization of LCD  */
	LCD_WRITE_COMMAND(mode_4bit);     /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_WRITE_COMMAND(display_on_cursur_off);              /* Display on cursor off*/
	LCD_WRITE_COMMAND(cursorToReght);              /* Increment cursor (shift cursor to right)*/
	LCD_WRITE_COMMAND(clear_lcd);
	LCD_WRITE_COMMAND(first_line_begin);/* Clear display screen*/
	_delay_ms(2);

	/*say hi*/
	LCD_WRITE_STRING("Hi");
	_delay_ms(3000);
	LCD_WRITE_COMMAND(clear_lcd);

	/*set the cursor to the begin of the next line*/
	LCD_WRITE_COMMAND(first_line_begin);



}

void LCD_WRITE_CHAR(u8 CHAR)
{
	LCD_PORT = (LCD_PORT & 0x0F) | (CHAR & 0xF0); /* sending upper nibble */
	LCD_PORT |= (1<<LCD_u8_RS);		/* RS=1, data reg. */
	LCD_PORT|= (1<<LCD_u8_E);
	_delay_us(1);

	LCD_PORT &= ~ (1<<LCD_u8_E);

		_delay_us(200);

		LCD_PORT = (LCD_PORT & 0x0F) | (CHAR << 4); /* sending lower nibble */
		LCD_PORT |= (1<<LCD_u8_E);
		_delay_us(1);
		LCD_PORT &= ~ (1<<LCD_u8_E);
		_delay_ms(2);
}

void LCD_WRITE_STRING(u8* buffer)
{
	int i;
		for(i=0;buffer[i]!=0;i++)		/* Send each char of string till the NULL */
		{
			LCD_WRITE_CHAR (buffer[i]);
		}
}

void LCD_WRITE_COMMAND(u8 command)
{
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0); /* sending upper nibble */
	LCD_PORT &= ~ (1<<LCD_u8_RS);		/* RS=0, command reg. */
	LCD_PORT |= (1<<LCD_u8_E);		/* Enable pulse */
	_delay_us(1);
	LCD_PORT &= ~ (1<<LCD_u8_E);

	_delay_us(200);

	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);  /* sending lower nibble */
	LCD_PORT |= (1<<LCD_u8_E);
	_delay_us(1);
	LCD_PORT &= ~ (1<<LCD_u8_E);
	_delay_ms(2);

}

void LCD_vidWriteNumber(u16 Copy_u16Number)
{
	u8 Counter=0,Digits=0,Current;
	u16 CopyNumber=Copy_u16Number;
	while(CopyNumber)
	{
		CopyNumber/=10;
		Digits++;
	}
	CopyNumber=Copy_u16Number;
	for(Counter=0;Counter<Digits;Counter++)
	{
		Current=CopyNumber/(Private_GetPower(10,Digits-1-Counter));
		LCD_WRITE_CHAR(Current+'0');
		CopyNumber%=(Private_GetPower(10,Digits-1-Counter));
	}

}
static u16 Private_GetPower(u8 Num1, u8 Num2)
{
	u16 Result=1;
	u8 Counter=0;
	for(Counter=0;Counter<Num2;Counter++)
	{
		Result*=Num1;
	}
	return Result;
}
void LCD_vidGotoxy (u8 Y,u8 X)
{
	if (X>0 && X<=16)
	{
		switch(Y)
		{
		case 1:
			LCD_WRITE_COMMAND(0x80+X-1);
			break;
		case 2:
			LCD_WRITE_COMMAND(0xC0+X-1);
			break;
		default:
			break;
		}
	}
}





