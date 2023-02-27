/*

SWC  :TIMERS
DATE :5/12/2022
*/

/*include LIB*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*include timer LIB*/
#include "TIMERS_interface.h"
#include "TIMERS_private.h"
#include "TIMERS_config.h"

/*ARRAY OF POINTERS TO FUNCTION THAT TAKE VOID AND RETURN VOID*/
/*FIRST ELEMENT FOR OVF AND SECOND ELEMENT FOR CTC FLAG FOR TIMER 0*/
static void(*TIMER_Apf[2])(void)={NULL,NULL};
//static void(*TIMERS_pfTIMER0OVF)(void);
//static void(*TIMERS_pfTIMER0CTC)(void);

/*implementation for founctions*/

void TIMERS_voidTIMERSInit(void)
{
    /*for timer0*/
    #if(TIMER0_INIT_STATE==TIMER_u8_INIT_STATE_DISABLE)/*check timer0 is disable */
    /*CLEAR BITS FOR PRESCALER TO DISABLE TIMER0*/
       CLR_BIT(TIMERS_u8_TCCR0_REG ,TIMERS_u8_CS00);
       CLR_BIT(TIMERS_u8_TCCR0_REG ,TIMERS_u8_CS01);
       CLR_BIT(TIMERS_u8_TCCR0_REG ,TIMERS_u8_CS02);
    #elif(TIMER0_INIT_STATE==TIMER_u8_INIT_STATE_ENABLE)/*check if timer0 is enable*/
       //TIMERS_u8_TCNT0_REG=TIMERS_u8TIMER0PreloadValue;
      /*choose mode of the timer0*/
      #if(TIMER0_u8Mode==TIMER0_u8FastPwmMode)   /*check fast pwm for timer0*/
        SET_BIT(TIMERS_u8_TCCR0_REG , TIMERS_u8_WGM00);
        SET_BIT(TIMERS_u8_TCCR0_REG , TIMERS_u8_WGM01);
        SET_BIT(TIMERS_u8_TIMSK_REG , TIMER_u8_OCIE0) ;  /*SET INTERRUPT FOR CTC FLAG*/

      #elif(TIMER0_u8Mode==TIMER0_u8PhaseCorrect)   /*check Phase Correct for timer 0*/
        SET_BIT(TIMERS_u8_TCCR0_REG , TIMERS_u8_WGM00);
        CLR_BIT(TIMERS_u8_TCCR0_REG , TIMERS_u8_WGM01);
        /*set OCR0  VALUE*/
        TIMERS_u8_OCR0_REG=TIMERS_u8OCR0_INITIAL_STATE;

       #elif(TIMER0_u8Mode==TIMER0_u8NormalMode)  /*check for NORMAL mode*/
        CLR_BIT(TIMERS_u8_TCCR0_REG , TIMERS_u8_WGM00);
        CLR_BIT(TIMERS_u8_TCCR0_REG , TIMERS_u8_WGM01);
        SET_BIT(TIMERS_u8_TIMSK_REG , TIMER_u8_TOIE0) ;  /*SET INTERRUPT FOR OVF FLAG*/

       #elif(TIMER0_u8Mode==TIMER0_u8CTCMode)  /*check for CTC mode*/
        CLR_BIT(TIMERS_u8_TCCR0_REG , TIMERS_u8_WGM00);
        SET_BIT(TIMERS_u8_TCCR0_REG , TIMERS_u8_WGM01);
        SET_BIT(TIMERS_u8_TIMSK_REG , TIMER_u8_OCIE0) ;  /*SET INTERRUPT FOR CTC FLAG*/
        /*set OCR0  VALUE*/
        TIMERS_u8_OCR0_REG=TIMERS_u8OCR0_INITIAL_STATE;
       #endif
       #if(TIMERS_u8OC0_Mode==TIMER_u8_NORMAL)
         CLR_BIT(TIMERS_u8_TCCR0_REG ,TIMERS_u8_COM00);
         CLR_BIT(TIMERS_u8_TCCR0_REG ,TIMERS_u8_COM01);
       #elif(TIMERS_u8OC0_Mode==TIMER_u8_TOGGLE)
         SET_BIT(TIMERS_u8_TCCR0_REG ,TIMERS_u8_COM00);
         CLR_BIT(TIMERS_u8_TCCR0_REG ,TIMERS_u8_COM01);
       #elif(TIMERS_u8OC0_Mode==TIMER_u8_SET)
         SET_BIT(TIMERS_u8_TCCR0_REG ,TIMERS_u8_COM00);
         SET_BIT(TIMERS_u8_TCCR0_REG ,TIMERS_u8_COM01);
       #elif(TIMERS_u8OC0_Mode==TIMER_u8_CLR)
         CLR_BIT(TIMERS_u8_TCCR0_REG ,TIMERS_u8_COM00);
         SET_BIT(TIMERS_u8_TCCR0_REG ,TIMERS_u8_COM01);
       #endif
       /*prescaler value*/
       #if(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_8)
         CLR_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS00)  ;
         SET_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS01);
         CLR_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS02) ;
       #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_64)
         SET_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS00)  ;
         SET_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS01);
         CLR_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS02) ;
       #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_256)
         CLR_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS00)
         CLR_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS01)
         SET_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS02)
       #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_1024)
         SET_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS00)
         CLR_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS01)
         SET_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS02)
       #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_FALLING_EDGE)
         CLR_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS00)
         SET_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS01)
         SET_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS02)
       #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_RAISING_EDGE)
         SET_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS00)
         SET_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS01)
         SET_BIT(TIMERS_u8_TCCR0_REG,TIMERS_u8_CS02)
       #endif
    #endif
		  /*for timer2*/
		    #if(TIMER2_INIT_STATE==TIMER_u8_INIT_STATE_DISABLE)
		    /*check timer2 is disable */
		    /*CLEAR BITS FOR PRESCALER TO DISABLE TIMER2*/
		       CLR_BIT(TIMERS_u8_TCCR2_REG ,TIMERS_u8_CS20);
		       CLR_BIT(TIMERS_u8_TCCR2_REG ,TIMERS_u8_CS21);
		       CLR_BIT(TIMERS_u8_TCCR2_REG ,TIMERS_u8_CS22);
		    #elif(TIMER2_INIT_STATE==TIMER_u8_INIT_STATE_ENABLE)/*check if timer2 is enable*/
		       //TIMERS_u8_TCNT2_REG=TIMERS_u8TIMER0PreloadValue;
		      /*choose mode of the timer2*/
		      #if(TIMER2_u8Mode==TIMER0_u8FastPwmMode)   /*check fast pwm for timer0*/
		        SET_BIT(TIMERS_u8_TCCR2_REG , TIMERS_u8_WGM20);
		        SET_BIT(TIMERS_u8_TCCR2_REG , TIMERS_u8_WGM21);
		        SET_BIT(TIMERS_u8_TIMSK_REG , TIMER_u8_OCIE2) ;  /*SET INTERRUPT FOR CTC FLAG*/

		      #elif(TIMER2_u8Mode==TIMER0_u8PhaseCorrect)   /*check Phase Correct for timer 0*/
		        SET_BIT(TIMERS_u8_TCCR2_REG , TIMERS_u8_WGM20);
		        CLR_BIT(TIMERS_u8_TCCR2_REG , TIMERS_u8_WGM21);
		        /*set OCR0  VALUE*/
		        TIMERS_u8_OCR2_REG=TIMERS_u8OCR0_INITIAL_STATE;

		       #elif(TIMER2_u8Mode==TIMER0_u8NormalMode)  /*check for NORMAL mode*/
		        CLR_BIT(TIMERS_u8_TCCR2_REG , TIMERS_u8_WGM20);
		        CLR_BIT(TIMERS_u8_TCCR2_REG , TIMERS_u8_WGM21);
		        SET_BIT(TIMERS_u8_TIMSK_REG , TIMER_u8_TOIE2) ;  /*SET INTERRUPT FOR OVF FLAG*/

		       #elif(TIMER2_u8Mode==TIMER0_u8CTCMode)  /*check for CTC mode*/
		        CLR_BIT(TIMERS_u8_TCCR2_REG , TIMERS_u8_WGM20);
		        SET_BIT(TIMERS_u8_TCCR2_REG , TIMERS_u8_WGM21);
		        SET_BIT(TIMERS_u8_TIMSK_REG , TIMER_u8_OCIE2) ;  /*SET INTERRUPT FOR CTC FLAG*/
		        /*set OCR0  VALUE*/
		        TIMERS_u8_OCR2_REG=TIMERS_u8OCR0_INITIAL_STATE;
		       #endif
		       #if(TIMERS_u8OC2_Mode==TIMER_u8_NORMAL)
		         CLR_BIT(TIMERS_u8_TCCR2_REG ,TIMERS_u8_COM20);
		         CLR_BIT(TIMERS_u8_TCCR2_REG ,TIMERS_u8_COM21);
		       #elif(TIMERS_u8OC2_Mode==TIMER_u8_TOGGLE)
		         SET_BIT(TIMERS_u8_TCCR2_REG ,TIMERS_u8_COM20);
		         CLR_BIT(TIMERS_u8_TCCR2_REG ,TIMERS_u8_COM21);
		       #elif(TIMERS_u8OC2_Mode==TIMER_u8_SET)
		         SET_BIT(TIMERS_u8_TCCR2_REG ,TIMERS_u8_COM20);
		         SET_BIT(TIMERS_u8_TCCR2_REG ,TIMERS_u8_COM21);
		       #elif(TIMERS_u8OC2_Mode==TIMER_u8_CLR)
		         CLR_BIT(TIMERS_u8_TCCR2_REG ,TIMERS_u8_COM20);
		         SET_BIT(TIMERS_u8_TCCR2_REG ,TIMERS_u8_COM21);
		       #endif
		       /*prescaler value*/
		       #if(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_8)
		         CLR_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS20)  ;
		         SET_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS21);
		         CLR_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS22) ;
		       #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_64)
		         SET_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS20)  ;
		         SET_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS21);
		         CLR_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS22) ;
		       #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_256)
		         CLR_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS20)
		         CLR_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS21)
		         SET_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS22)
		       #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_1024)
		         SET_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS20)
		         CLR_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS21)
		         SET_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS22)
		       #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_FALLING_EDGE)
		         CLR_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS20)
		         SET_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS21)
		         SET_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS22)
		       #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_RAISING_EDGE)
		         SET_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS20)
		         SET_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS21)
		         SET_BIT(TIMERS_u8_TCCR2_REG,TIMERS_u8_CS22)
		       #endif
#endif

				 /*TIMER 1 INIT*/
				 #if(TIMER1_INIT_STATE ==TIMER_u8_INIT_STATE_DISABLE)
				       CLR_BIT(TIMERS_u8_TCCR1B_REG ,TIMERS_u8_CS10);
				       CLR_BIT(TIMERS_u8_TCCR1B_REG ,TIMERS_u8_CS11);
				       CLR_BIT(TIMERS_u8_TCCR1B_REG ,TIMERS_u8_CS12);
				 #elif(TIMER1_INIT_STATE==TIMER_u8_INIT_STATE_ENABLE)
				     #if(TIMER1_u8Mode==TIMER1_u8FastPwmMode_iCR1_TOP)
				     /*SELECT FAST PWM MODE OF TIMER 1*/
				       SET_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_WGM12);
				       SET_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_WGM13);
				       SET_BIT(TIMERS_u8_TCCR1A_REG,TIMERS_u8_WGM11);
				       CLR_BIT(TIMERS_u8_TCCR1A_REG,TIMERS_u8_WGM10);
				       /*set ICR VALUE FLAG*/
				       TIMERS_u16_ICR1_REG=TIMER1_u16_ICR1_VALUE;

				     #elif(TIMER1_u8Mode==TIMER1_u8NormalMode)
				       CLR_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_WGM12);
				       CLR_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_WGM13);
				       CLR_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_WGM11);
				       CLR_BIT(TIMERS_u8_TCCR1A_REG,TIMERS_u8_WGM10);

				       /*set interrupt enable bit*/
				       SET_BIT(TIMERS_u8_TIMSK_REG,TIMER_u8_TOIE1);
				     #endif
				     #if(TIMERS_u8OC1A_Mode==TIMER_u8_CLR)
				     SET_BIT(TIMERS_u8_TCCR1A_REG,TIMERS_u8_COM1A1);
				     CLR_BIT(TIMERS_u8_TCCR1A_REG,TIMERS_u8_COM1A0);
				 #endif
				     #if(TIMERS_u8OC1B_Mode==TIMER_u8_CLR)
				     SET_BIT(TIMERS_u8_TCCR1A_REG,TIMERS_u8_COM1B1);
				     CLR_BIT(TIMERS_u8_TCCR1A_REG,TIMERS_u8_COM1B0);
				     #endif

				     /*prescaler value*/
				     #if(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_8)
				       CLR_BIT(TIMERS_u8_TCCR1B_REG_REG,TIMERS_u8_CS10)  ;
				       SET_BIT(TIMERS_u8_TCCR1B_REG_REG,TIMERS_u8_CS11);
				       CLR_BIT(TIMERS_u8_TCCR1B_REG_REG,TIMERS_u8_CS12) ;
				     #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_64)
				       SET_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS10) ;
				       SET_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS11);
				       CLR_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS12) ;
				     #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_256)
				       CLR_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS10)
				       CLR_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS11)
				       SET_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS12)
				     #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_1024)
				       SET_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS10)
				       CLR_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS11)
				       SET_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS12)
				     #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_FALLING_EDGE)
				       CLR_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS10)
				       SET_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS11)
				       SET_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS12)
				     #elif(TIMERS_u8_PRESCALER==TIMERs_u8TIMER0PreScaler_RAISING_EDGE)
				       SET_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS10)
				       SET_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS11)
				       SET_BIT(TIMERS_u8_TCCR1B_REG,TIMERS_u8_CS12)
				 #endif
#endif

}

u8   TIMERS_u8TIMERSetCallBack(void(*copy_pf)(void),u8 copy_u8TimerIndex)
{
    u8 loacal_u8ErrorState=STD_TYPES_OK;
    if(copy_pf!=NULL)
    {
         TIMER_Apf[copy_u8TimerIndex]=copy_pf;
    }
    else
    {
        loacal_u8ErrorState=STD_TYPES_NOK;
    }

    return loacal_u8ErrorState;
}

void TIMERS_timer0SetCompareMatchValue(u8 compareValue)
{
	TIMERS_u8_OCR0_REG=compareValue;
}
void TIMER_timer1SetCompareMatchAValue(u16 compareValue)
{
	// Init Timer With Compare Value
	 TIMERS_u16_OCR1A_REG = compareValue;
}


 /*ISR FOT OVF OF TIMER 0*/
/*
void __vector_11(void)       __attribute__((signal));
void __vector_11(void)
{
    static u16 local_u16_counterOVF=0;
    local_u16_counterOVF++;
    if(local_u16_counterOVF==TIMERS_u8NumberOfOVS)
    {
        TIMERS_u8_TCNT0_REG=TIMERS_u8TIMER0PreloadValue;
        local_u16_counterOVF=0;
        if(TIMER_Apf[TIMERS_u8_OVF_INDEX]!=NULL)
           {
               TIMER_Apf[TIMERS_u8_OVF_INDEX]();
           }
    }

}
void __vector_10(void)       __attribute__((signal));
void __vector_10(void)
{
	static u16 local_u16_counterCTC=0;
	local_u16_counterCTC++;
	if(local_u16_counterCTC==2500)
	{
		local_u16_counterCTC=0;
		if(TIMER_Apf[TIMERS_u8_CTC_INDEX]!=NULL)
		{
			TIMER_Apf[TIMERS_u8_CTC_INDEX]();
		}


	}

}*/





