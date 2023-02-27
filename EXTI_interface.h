/*

SWC  :EXTI
DATE :4/12/2022
*/
#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/*define bits registers*/

/*bits for MCUCR  */
#define EXTI_u8_ISC00                                 0
#define EXTI_u8_ISC01                                 1
#define EXTI_u8_ISC10                                 2
#define EXTI_u8_ISC11                                 3

/*bits for MCUCSR  */
#define EXTI_u8_ISC2                                  6

/*bits for  GICR  */
#define EXTI_u8Bit_INT0                               6
#define EXTI_u8Bit_INT1                               7
#define EXTI_u8Bit_INT2                               5

/*bits for  GIFR  */

#define EXTI_u8_INTF0                                 6
#define EXTI_u8_INTF1                                 7
#define EXTI_u8_INTF2                                 5
                
/*macros for EXT_interrupts*/                         
#define EXTI_u8_INT0                                  0
#define EXTI_u8_INT1                                  1
#define EXTI_u8_INT2                                  2

/*macros for edge source*/
#define EXTI_u8_RAISING_EDGE                          0
#define EXTI_u8_FALLING_EDGE                          1
#define EXTI_u8_ANY_LOGICAL_CHANGE_EDGE               2 
#define EXTI_u8_LOW_LEVEL_EDGE                        3 

u8 EXTI_u8EXTIEnabele(u8 copy_u8EXTIIndex,u8 copy_u8EdgeIndex);
u8 EXTI_u8EXTIDisable(u8 copy_u8EXTIIndex);
u8 EXTI_u8SetCallBack(u8 copy_u8EXTIIndex , void (*copy_pf)(void));



#endif
