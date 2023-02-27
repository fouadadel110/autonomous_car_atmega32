/*

SWC  :GI
DATE :4/12/2022
*/
/*include LIB*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*include EXTI LIB*/
#include "GI_interface.h"

/* DEFINE REG FOR GLOBAL INTERRUPT*/

#define   GLBI_u8_SREG_REG        *((volatile u8 *)0x5F)

/*global interrupt pin*/

#define GLBI_u8_I                  7

/*implementation of functions */

void  GI_voidEnbale(void)
{
    SET_BIT(GLBI_u8_SREG_REG,GLBI_u8_I);
}
void GI_voidDissable(void)
{
    CLR_BIT(GLBI_u8_SREG_REG,GLBI_u8_I);
}
