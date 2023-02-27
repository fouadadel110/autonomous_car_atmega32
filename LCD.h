#ifndef LCD_H
#define LCD_H

#define LCD_u8_D4          4
#define LCD_u8_D5          5
#define LCD_u8_D6          6
#define LCD_u8_D7          7
#define LCD_u8_RS          0   
#define LCD_u8_E           2

#define LCD_port_DIR      DIO_u8_PORTA
#define LCD_PORT          DIO_u8_PORTA_REG
 
/*define LCD commands*/
#define lcd_on_cursor_on        0X0F
#define clear_lcd				0X01
#define shift_cursor_r			0X14
#define shift_cursor_l			0X10
#define first_line_begin		0X80
#define second_line_begin		0Xc0
#define mode_8bit				0X38
#define mode_4bit				0X28
#define display_on_cursur_off	0X0C
#define cursorToLeft            0X04
#define cursorToReght           0X06


void LCD_INIT();
void LCD_WRITE_STRING(u8* buffer);
void LCD_WRITE_CHAR(u8 CHAR);
void LCD_WRITE_COMMAND(u8 command);
void LCD_vidWriteNumber(u16 Copy_u16Number);
static u16 Private_GetPower(u8 Num1, u8 Num2);
void LCD_vidGotoxy (u8 Y,u8 X);
/***************************************************************************************/
/* Description! Interface to write extra characters saved in the CGRAM                 */
/* Input      ! Y = Row position , X = Column position                                 */
/* Output     ! Nothing                                                                */
#endif 
