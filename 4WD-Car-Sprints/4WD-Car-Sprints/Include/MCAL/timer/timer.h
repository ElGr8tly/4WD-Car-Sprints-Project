/*
*****************************************************************************************************************
    Author 		: Mahmoud Mahran
    Version		: V:1.0
	Date 		: 03/10/2023
Description 	: timer.h --> Prototypes
*****************************************************************************************************************

What to sell for customer
	1- the Architecture of the API
	2- Name of the functions
	3- The outputs
	4- macros
*/

/*
*************************************************************************************************************************
*************************************************************************************************************************
**************************************************File Guard*************************************************************
*************************************************************************************************************************
*/

#ifndef TIMER_H
#define TIMER_H

/***************************************************/
/**           TIMER INTERRUPT REGISTERS           **/
/***************************************************/
#define TIMSK              *( (volatile u8*)0x59)
#define TOIE0              0
#define OCIE0              1
#define TOIE1              2
#define OCIE1B             3
#define OCIE1A             4
#define TICIE1             5
#define TOIE2              6
#define OCIE2              7
#define TIFR               *( (volatile u8*)0x58)
#define TOV0               0
#define OCF0               1
#define TOV1               2
#define OCF1B              3
#define OCF1A              4
#define ICF1               5
#define TOV2               6
#define OCF2               7
/***************************************************/
/**            TIMER0 REGISTERS                   **/
/***************************************************/
#define TCCR0              *( (volatile u8*)0x53)
#define CS00               0
#define CS01               1
#define CS02               2
#define WGM01              3
#define COM00              4
#define COM01              5
#define WGM00              6
#define FOC0               7
#define TCNT0              *( (volatile u8*)0x52)
#define OCR0               *( (volatile u8*)0x5C)
/***************************************************/
/**            TIMER1 REGISTERS                   **/
/***************************************************/
#define TCCR1A             *( (volatile u8*)0x4F)
#define WGM10              0
#define WGM11              1
#define FOC1B              2
#define FOC1A              3
#define COM1B0             4
#define COM1B1             5
#define COM1A0             6
#define COM1A1             7
#define TCCR1B             *( (volatile u8*)0x4E)
#define CS10               0
#define CS11               1
#define CS12               2
#define WGM12              3
#define WGM13              4
#define ICES1              6
#define ICNC1              7
#define TCNT1H             *( (volatile u8*)0x4D)
#define TCNT1L             *( (volatile u8*)0x4C)
#define OCR1AH             *( (volatile u8*)0x4B)
#define OCR1AL             *( (volatile u8*)0x4A)
#define OCR1BH             *( (volatile u8*)0x49)
#define OCR1BL             *( (volatile u8*)0x48)
#define ICR1H              *( (volatile u8*)0x47)
#define ICR1L              *( (volatile u8*)0x46)
///////////////////////CONFIG MACROS/////////////////////////
#define ENABLE                                           1
#define DISABLE                                          0
#define NO_PRE                                           1U
#define PRE_8                                            2U
#define PRE_64                                           3U
#define PRE_256                                          4U
#define PRE_1024                                         5U
#define EXT_FALLING                                      6U
#define EXT_RISING                                       7U
#define NORMAL                                           0x00
//TIMER0 macros
#define CTC                                              0x08
#define PWM_PHASE_CORRECT                                0x40
#define FAST_PWM                                         0x48
#define OC0_OFF                                          0U
#define TGL_OC0                                          1U
#define CLR_OC0                                          2U
#define SET_OC0                                          3U
//TIMER1 macros
#define PWM_PHASE_CORRECT_8_BIT                          0x01
#define PWM_PHASE_CORRECT_9_BIT                          0x02
#define PWM_PHASE_CORRECT_10_BIT                         0x03
#define CTC_OCR1A_TOP                                    0x04
#define FAST_PWM_8_BIT                                   0x05
#define FAST_PWM_9_BIT                                   0x06
#define FAST_PWM_10_BIT                                  0x07
#define PWM_PHASE_FREQ_CORRECT_ICR1_TOP                  0x08
#define PWM_PHASE_FREQ_CORRECT_OCR1A_TOP                 0x09
#define PWM_PHASE_CORRECT_ICR1_TOP                       0x0A
#define PWM_PHASE_CORRECT_OCR1A_TOP                      0x0B
#define CTC_ICR1_TOP                                     0x0C
#define FAST_PWM_ICR1_TOP                                0x0E
#define FAST_PWM_OCR1A_TOP                               0x0F

#define OC1_OFF                                          0U
#define TGL_OC1                                          1U
#define CLR_OC1                                          2U
#define SET_OC1                                          3U



///////////////Define System CLK///////////////
#ifndef F_CPU
#define F_CPU         8000000UL
#endif
///////////////Enable Or Disable Timers///////////////
#define TIMER_0			    ENABLE
#define TIMER_1			    ENABLE

/******************************************************************************************/
/*********************************TIMER0 CONFIG********************************************/
/******************************************************************************************/

///////////////CHOOSE MODE OF OPERATION///////////////
/* Timer/Counter Mode of Operation | TOP | Update of OCR0 | TOV0 Flag Set-on
-----------------------------------|-----|----------------|-----------------
               NORMAL              |0xFF |    Immediate   |      MAX
               CTC                 |0xFF |       TOP      |     BOTTOM
               PWM_PHASE_CORRECT   |OCR0 |    Immediate   |      MAX
               FAST_PWM            |0xFF |     BOTTOM     |      MAX
 */
#define TIMER_0_MODE         NORMAL
///////////////CHOOSE NORMAL/CTC MODE CONFIG///////////////
/*options in Compare Output Mode, non-PWM Mode
OC0_OFF: Normal port operation, OC0 disconnected.
TGL_OC0: Toggle OC0 on compare match
CLR_OC0: Clear OC0 on compare match
SET_OC0: Set OC0 on compare match
*/
#define TIMER_0_NORMAL       TGL_OC0
///////////////CHOOSE TIMER0 CLOCK SOURCE///////////////
/*options   :
NO_PRE      : F_CPU (No prescaling)
PRE_8       : F_CPU / 8 (From prescaler)
PRE_64      : F_CPU / 64 (From prescaler)
PRE_256     : F_CPU / 256 (From prescaler)
PRE_1024    : F_CPU / 1024 (From prescaler)
EXT_FALLING : External clock source on T0 pin. Clock on falling edge.
EXT_RISING  : External clock source on T0 pin. Clock on rising edge.
*/
#define TIMER_0_CLK           PRE_8
///////////////ENABLE TIMER0 INTERRUPTS///////////////
#define TIMER_0_OC_INTERRUPT  DISABLE
#define TIMER_0_OVF_INTERRUPT ENABLE
/******************************************************************************************/
/*********************************TIMER1 CONFIG********************************************/
/******************************************************************************************/
///////////////CHOOSE MODE OF OPERATION///////////////
/* Timer/Counter Mode of Operation |  TOP  | Update of OCR1x | TOV1 Flag Set-on
-----------------------------------|-------|-----------------|-----------------
NORMAL                             |0xFFFF |Immediate        |MAX
PWM_PHASE_CORRECT_8_BIT            |0x00FF |TOP              |BOTTOM
PWM_PHASE_CORRECT_9_BIT            |0x01FF |TOP              |BOTTOM
PWM_PHASE_CORRECT_10_BIT           |0x03FF |TOP              |BOTTOM
CTC_OCR1A_TOP                      |OCR1A  |Immediate        |MAX
FAST_PWM_8_BIT                     |0x00FF |BOTTOM           |TOP
FAST_PWM_9_BIT                     |0x01FF |BOTTOM           |TOP
FAST_PWM_10_BIT                    |0x03FF |BOTTOM           |TOP
PWM_PHASE_FREQ_CORRECT_ICR1_TOP    |ICR1   |BOTTOM           |BOTTOM
PWM_PHASE_FREQ_CORRECT_OCR1A_TOP   |OCR1A  |BOTTOM           |BOTTOM
PWM_PHASE_CORRECT_ICR1_TOP         |ICR1   |TOP              |BOTTOM
PWM_PHASE_CORRECT_OCR1A_TOP        |OCR1A  |TOP              |BOTTOM
CTC_ICR1_TOP                       |ICR1   |Immediate        |MAX
FAST_PWM_ICR1_TOP                  |ICR1   |BOTTOM           |TOP
FAST_PWM_OCR1A_TOP                 |OCR1A  |BOTTOM           |TOP
*/
#define TIMER_1_MODE         NORMAL
///////////////CHOOSE NORMAL/CTC MODE CONFIG FOR CH A & CH B///////////////
/*options in Compare Output Mode, non-PWM Mode
OC1_OFF: Normal port operation, OC1A/OC1B disconnected.
TGL_OC1: Toggle OC1A/OC1B on compare match
CLR_OC1: Clear OC1A/OC1B on compare match (Set output to low level)
SET_OC1: Set OC1A/OC1B on compare match (Set output to high level)
*/
#define TIMER_1_NORMAL_A     TGL_OC1
#define TIMER_1_NORMAL_B     TGL_OC1
///////////////CHOOSE TIMER1 CLOCK SOURCE///////////////
/*options   :
NO_PRE      : F_CPU (No prescaling)
PRE_8       : F_CPU / 8 (From prescaler)
PRE_64      : F_CPU / 64 (From prescaler)
PRE_256     : F_CPU / 256 (From prescaler)
PRE_1024    : F_CPU / 1024 (From prescaler)
EXT_FALLING : External clock source on T1 pin. Clock on falling edge
EXT_RISING  : External clock source on T1 pin. Clock on rising edge.
*/
#define TIMER_1_CLK           PRE_64
///////////////ENABLE TIMER1 INTERRUPTS///////////////
#define TIMER_1_IC_INTERRUPT  DISABLE
#define TIMER_1_OCA_INTERRUPT DISABLE
#define TIMER_1_OCB_INTERRUPT DISABLE
#define TIMER_1_OVF_INTERRUPT ENABLE

//driver interfacing macros
#define    TIMER_TM0			0
#define    TIMER_TM1			1
//TIMERS INTERRUPTS
#define    TIMER1_OVF           0
#define    TIMER0_OVF           1
typedef enum en_timerError{
	TIMER_OK,
	TIMER_WRONG_INPUT,
	TIMER_NOK
	}en_timerError;
/***
 * initializes TIMERS based on the selected config, returns void
 * INPUT: void
 * OUTPUT: void
 * Returns: en_timerError, (ex: TIMER_OK, TIMER_WRONG_INPUT, TIMER_NOK…)
 * **/
en_timerError TIMER_init(void);
/***
 * Starts a specific TIMER based on input, returns void
 * INPUT: (u8) Timer to start
 * OUTPUT: void
 * Returns: en_timerError, (ex: TIMER_OK, TIMER_WRONG_INPUT, TIMER_NOK…)
 * **/
en_timerError TIMER_start(u8 u8_a_timerNumber);
/***
 * Stops a specific TIMER based on input, returns void
 * INPUT: (u8) Timer to stop
 * OUTPUT: void
 * Returns: en_timerError, (ex: TIMER_OK, TIMER_WRONG_INPUT, TIMER_NOK…)
 * **/
en_timerError TIMER_stop(u8 u8_a_timerNumber);
/***
 * Reads a specific TIMER's current value(counter register) based on input, returns void
 * INPUT: (u8) Timer to read, (u16*) pointer to store the value
 * OUTPUT: (u16) timer current value
 * Returns: en_timerError, (ex: TIMER_OK, TIMER_WRONG_INPUT, TIMER_NOK…)
 * **/
en_timerError TIMER_read(u8 u8_a_timerNumber, u16* u16_a_tTimerValue);
/***
 * Preloads a specific TIMER value(counter register) based on input, returns void
 * INPUT:(u16) preload value , (u8) Timer to preload
 * OUTPUT: void
 * Returns: en_timerError, (ex: TIMER_OK, TIMER_WRONG_INPUT, TIMER_NOK…)
 * **/
en_timerError TIMER_preload(u16 u16_a_value, u8 u8_a_timerNumber);
/***
 * Sets the callback function for the input timer interrupt, returns void
 * INPUT: (u8) timer interrupt name, (*ptr) call back function
 * OUTPUT: void
 * Returns: en_timerError, (ex: TIMER_OK, TIMER_WRONG_INPUT, TIMER_NOK…)
 * **/
en_timerError TIMER_setCallBack(u8 u8_a_timerInterruptNum, void (*v_a_ptr)(void));
#endif /* TIMER_H_ */