/*

SWC  :TIMERS
DATE :5/12/2022
*/

/*macros for  TIMSK BITS*/
/*for timer 0*/
#define TIMER_u8_TOIE0                 0
#define TIMER_u8_OCIE0                 1
/*for timer 1*/
#define TIMER_u8_TOIE1                 2
#define TIMER_u8_OCIE1B                3
#define TIMER_u8_OCIE1A                4
#define TIMER_u8_TICIE1                5
/*for timer 2*/
#define TIMER_u8_TOIE2                 6
#define TIMER_u8_OCIE2                 7

/*macros for  TIFR BITS*/
/*for timer 0*/
#define TIMER_u8_TOV0                  0
#define TIMER_u8_OCF0                  1
/*for timer 1*/
#define TIMER_u8_TOV1                  2
#define TIMER_u8_OCF1B                 3
#define TIMER_u8_OCF1A                 4
#define TIMER_u8_ICF1                  5
/*for timer 2*/
#define TIMER_u8_TOV2                  6
#define TIMER_u8_OCF2                  7


/*macros for TCCR0 BITS*/  /*timer 0*/
#define TIMERS_u8_CS00                 0   
#define TIMERS_u8_CS01                 1
#define TIMERS_u8_CS02                 2
#define TIMERS_u8_WGM01                3
#define TIMERS_u8_COM00                4
#define TIMERS_u8_COM01                5
#define TIMERS_u8_WGM00                6
#define TIMERS_u8_FOC0                 7



/*macros for TCCR2 BITS*/  /*timer 2*/
#define TIMERS_u8_CS20                 0
#define TIMERS_u8_CS21                 1
#define TIMERS_u8_CS22                 2
#define TIMERS_u8_WGM21                3
#define TIMERS_u8_COM20                4
#define TIMERS_u8_COM21                5
#define TIMERS_u8_WGM20                6
#define TIMERS_u8_FOC2                 7


/*macros for TCCR1A BITS*/  /*timer 1A*/
#define TIMERS_u8_WGM10                0
#define TIMERS_u8_WGM11                1
#define TIMERS_u8_FOC1B                2
#define TIMERS_u8_FOC1A                3
#define TIMERS_u8_COM1B0               4
#define TIMERS_u8_COM1B1               5
#define TIMERS_u8_COM1A0               6
#define TIMERS_u8_COM1A1               7


/*macros for TCCR1B BITS*/  /*timer 1B*/

#define TIMERS_u8_CS10                 0
#define TIMERS_u8_CS11                 1
#define TIMERS_u8_CS12                 2
#define TIMERS_u8_WGM12                3
#define TIMERS_u8_WGM13                4

#define TIMERS_u8_ICES1                6
#define TIMERS_u8_CNC1                 7



/*functions timers prototype*/

void TIMERS_voidTIMERSInit(void);
u8   TIMERS_u8TIMERSetCallBack(void(*copy_pf)(void),u8 copy_u8TimerIndex);
void TIMERS_timer0SetCompareMatchValue(u8 compareValue);
void TIMER_timer1SetCompareMatchAValue(u16 compareValue);



