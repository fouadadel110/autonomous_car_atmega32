/*

SWC  :TIMERS
DATE :5/12/2022
*/


/*macros for ENABLE OR DISABLE*/
#define TIMER_u8_INIT_STATE_ENABLE     1
#define TIMER_u8_INIT_STATE_DISABLE    0


/*macros for initila states*/
#define TIMER0_INIT_STATE    TIMER_u8_INIT_STATE_ENABLE
#define TIMER1_INIT_STATE    TIMER_u8_INIT_STATE_ENABLE
#define TIMER2_INIT_STATE    TIMER_u8_INIT_STATE_ENABLE


/*macros for MODES FOR TIMER0*/

/*modes for timer0*/
#define TIMER0_u8NormalMode   0
#define TIMER0_u8CTCMode      1
#define TIMER0_u8FastPwmMode  2
#define TIMER0_u8PhaseCorrect 3


/*modes for timer1*/
#define  TIMER1_u8FastPwmMode_iCR1_TOP     0
#define  TIMER1_u8NormalMode               1
/*modes for timer2*/

/*select mode for timer*/
#define TIMER0_u8Mode         TIMER0_u8FastPwmMode
#define TIMER1_u8Mode         TIMER1_u8FastPwmMode_iCR1_TOP
#define TIMER2_u8Mode         TIMER_u8NormalMode 

/*macros for modes in OC PIN*/
#define TIMER_u8_CLR            0
#define TIMER_u8_SET            1
#define TIMER_u8_TOGGLE         2
#define TIMER_u8_NORMAL         3




/*macro for OCR0 INITIALS*/
#define TIMERS_u8OCR0_INITIAL_STATE                         0
/*macro for OC0 mode*/
#define TIMERS_u8OC0_Mode                                   TIMER_u8_CLR



/*macros for OC1A mode*/
#define TIMERS_u8OC1A_Mode        TIMER_u8_CLR
#define TIMERS_u8OC1B_Mode        TIMER_u8_CLR


/*macros for prescaler*/
#define TIMERS_u8_PRESCALER                                 TIMERs_u8TIMER0PreScaler_64
#define TIMERs_u8TIMER0PreScaler_8                          0  
#define TIMERs_u8TIMER0PreScaler_64                         1   
#define TIMERs_u8TIMER0PreScaler_256                        2 
#define TIMERs_u8TIMER0PreScaler_1024                       3 
#define TIMERs_u8TIMER0PreScaler_FALLING_EDGE               4  
#define TIMERs_u8TIMER0PreScaler_RAISING_EDGE               5

/*macro for PRELOAD VALUE*/

#define TIMERS_u8TIMER0PreloadValue                         0

/*macro for numbers of OVFS*/
#define TIMERS_u8NumberOfOVS                                977

/*MACRO FOR TIMER OVF FLAG INDEX*/
#define TIMERS_u8_OVF_INDEX                                 0
/*MACRO FOR TIMER OVF FLAG INDEX*/
#define TIMERS_u8_CTC_INDEX                                 1
/*ICR VALUE*/
#define TIMER1_u16_ICR1_VALUE                               4999
