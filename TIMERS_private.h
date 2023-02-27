/*

SWC  :TIMERS
DATE :5/12/2022
*/

#ifndef TIMERS_PRIVATE_H_
#define TIMERS_PRIVATE_H_
/*DEFINE TIMER 0 REGISTERS*/ /*8-bit TIMER/COUNTER*/
#define TIMERS_u8_TCCR0_REG        *((volatile u8*)0x53) /*Timer/Counter Control Register*/
#define TIMERS_u8_TCNT0_REG        *((volatile u8*)0x52) /*Timer/Counter Register*/
#define TIMERS_u8_OCR0_REG         *((volatile u8*)0x5C) /*Output Compare Register*/

/*DEFINE TIMER 2 REGISTERS*/ /*8-bit TIMER/COUNTER*/
#define TIMERS_u8_TCCR2_REG        *((volatile u8*)0x45) /*Timer/Counter Control Register*/
#define TIMERS_u8_TCNT2_REG        *((volatile u8*)0x44) /*Timer/Counter Register*/
#define TIMERS_u8_OCR2_REG         *((volatile u8*)0x43) /*Output Compare Register*/

/*DEFINE TIMER 1 REGISTERS*/ /*16-bit TIMER/COUNTER*/
#define TIMERS_u8_TCCR1A_REG       *((volatile u8*)0x4F) /*Timer/Counter Control Register*/ /*A*/
#define TIMERS_u8_TCCR1B_REG       *((volatile u8*)0x4E) /*Timer/Counter Control Register*/ /*B*/
#define TIMERS_u16_OCR1A_REG       *((volatile u16*)0x4A) /*Output Compare Register*/ /*A*/
#define TIMERS_u16_OCR1B_REG       *((volatile u16*)0x48) /*Output Compare Register*/ /*B*/
#define TIMERS_u16_ICR1_REG        *((volatile u16*)0x46)
#define TIMERS_u16_TCNT1_REG       *((volatile u16*)0x4C) /*Timer/Counter Register for timer1*/
 

/*Timer/Counter Interrupt Mask Register*/
#define TIMERS_u8_TIMSK_REG        *((volatile u8*)0x59)
  
/*Timer/Counter Interrupt Flag Register */
#define TIMERS_u8_TIFR_REG         *((volatile u8*)0x58)


#endif
