/*

SWC  :EXTI
DATE :4/12/2022
*/
/*include LIB*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*include EXTI LIB*/
#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"

/*global array of  pointers to function*/
static void (*EXTI_ApfEXTI[3])(void)={NULL,NULL,NULL};


/*implementation of functions */
u8 EXTI_u8EXTIEnabele(u8 copy_u8EXTIIndex,u8 copy_u8EdgeIndex)
{
    u8 localStateError=STD_TYPES_OK;
    switch(copy_u8EXTIIndex)
    {
        case EXTI_u8_INT0 :
        switch(copy_u8EdgeIndex)
        {
            case EXTI_u8_RAISING_EDGE:
            SET_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC00 );
            SET_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC01 );
            SET_BIT(EXTI_u8_GICR_REG  , EXTI_u8Bit_INT0 );
            break;

            case EXTI_u8_FALLING_EDGE:
            CLR_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC00 );
            SET_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC01 );
            SET_BIT(EXTI_u8_GICR_REG  , EXTI_u8Bit_INT0 );
            break;

            case EXTI_u8_ANY_LOGICAL_CHANGE_EDGE:
            SET_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC00 );
            CLR_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC01 );
            SET_BIT(EXTI_u8_GICR_REG  , EXTI_u8Bit_INT0 );
            break;

            case EXTI_u8_LOW_LEVEL_EDGE:
            CLR_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC00 );
            CLR_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC01 );
            SET_BIT(EXTI_u8_GICR_REG  , EXTI_u8Bit_INT0 );
            break;

            default : localStateError=STD_TYPES_NOK;
            break;
        }
        break;

        case EXTI_u8_INT1 :
        switch(copy_u8EdgeIndex)
        {
            case EXTI_u8_RAISING_EDGE:
            SET_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC10 ); 
            SET_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC11 );
            SET_BIT(EXTI_u8_GICR_REG  , EXTI_u8Bit_INT1 );
            break;

            case EXTI_u8_FALLING_EDGE:
            CLR_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC10 );
            SET_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC11 );
            SET_BIT(EXTI_u8_GICR_REG  , EXTI_u8Bit_INT1 );
            break;

            case EXTI_u8_ANY_LOGICAL_CHANGE_EDGE:
            SET_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC10 );
            CLR_BIT(EXTI_u8_MCUCR_REG , EXTI_u8_ISC11 );
            SET_BIT(EXTI_u8_GICR_REG  , EXTI_u8Bit_INT1 );
            break;

            case EXTI_u8_LOW_LEVEL_EDGE:
            CLR_BIT( EXTI_u8_MCUCR_REG , EXTI_u8_ISC10 );
            CLR_BIT( EXTI_u8_MCUCR_REG , EXTI_u8_ISC11 );
            SET_BIT( EXTI_u8_GICR_REG  , EXTI_u8Bit_INT1 );
            break;

            default : localStateError=STD_TYPES_NOK;
            break;
        }   
        break;

        case EXTI_u8_INT2 :
        switch(copy_u8EdgeIndex)
        {
            case EXTI_u8_RAISING_EDGE:
            SET_BIT( EXTI_u8_MCUCSR_REG ,EXTI_u8_ISC2 );
            SET_BIT( EXTI_u8_GICR_REG , EXTI_u8Bit_INT2 );
            break;

            case EXTI_u8_FALLING_EDGE:
            CLR_BIT( EXTI_u8_MCUCSR_REG ,EXTI_u8_ISC2 );
            SET_BIT( EXTI_u8_GICR_REG , EXTI_u8Bit_INT2 );
            break;

            default : localStateError=STD_TYPES_NOK;
            break;
        }
        break;

        default : localStateError=STD_TYPES_NOK;
        break;

    }
    return localStateError;

}
u8 EXTI_u8EXTIDisable(u8 copy_u8EXTIIndex)
{
    u8 localStateError=STD_TYPES_OK;
    switch(copy_u8EXTIIndex)
    {
        case EXTI_u8_INT0 :
        CLR_BIT(EXTI_u8_GICR_REG  , EXTI_u8Bit_INT0 );
        break;

        case EXTI_u8_INT1 :
        CLR_BIT(EXTI_u8_GICR_REG  , EXTI_u8Bit_INT1 );
        break;

        case EXTI_u8_INT2 :
        CLR_BIT(EXTI_u8_GICR_REG  , EXTI_u8Bit_INT2 );
        break;

        default : localStateError=STD_TYPES_NOK;
        break;
    }
    return localStateError;

}


u8 EXTI_u8SetCallBack(u8 copy_u8EXTIIndex , void (*copy_pf)(void))
{
    u8 localStateError=STD_TYPES_OK;
    if((copy_u8EXTIIndex <= EXTI_u8_INT2 ) && (copy_pf!=NULL))
    {
        EXTI_ApfEXTI[copy_u8EXTIIndex]=copy_pf;
    }
    else
    {
        localStateError=STD_TYPES_NOK;
    }
    return localStateError;
}


/*implementation for ISR for EXTI0*/
void __vector_1(void)    __attribute((signal));
void __vector_1(void)
{
    if(EXTI_ApfEXTI[EXTI_u8_INTF0] !=NULL)
    {
	     EXTI_ApfEXTI[0]();
    }
}

/*implementation for ISR for EXTI1*/
void __vector_2(void)    __attribute((signal));
void __vector_2(void)
{
	if(EXTI_ApfEXTI[EXTI_u8_INTF1] !=NULL)
    {
	     EXTI_ApfEXTI[1]();
    }
}

/*implementation for ISR for EXTI2*/
void __vector_3(void)    __attribute((signal));
void __vector_3(void)
{
	if(EXTI_ApfEXTI[EXTI_u8_INTF2] !=NULL)
    {
	     EXTI_ApfEXTI[2]();
    }
}


