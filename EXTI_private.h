/*

SWC  :EXTI
DATE :4/12/2022
*/
#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_
/*Define External interrupt registers*/

#define   EXTI_u8_MCUCR_REG                         *((volatile u8 *)0x55)
#define   EXTI_u8_MCUCSR_REG                        *((volatile u8 *)0x54)
#define   EXTI_u8_GICR_REG                          *((volatile u8 *)0x5B)
#define   EXTI_u8_GIFR_REG                          *((volatile u8 *)0x5A)


                            
                            

#endif
