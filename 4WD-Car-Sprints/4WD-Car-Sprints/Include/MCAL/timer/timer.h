#ifndef TIMER_H
#define TIMER_H

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
/***************************************************/
/**            TIMER2 REGISTERS                   **/
/***************************************************/
#define TCCR2              *( (volatile u8*)0x45)
#define CS20               0
#define CS21               1
#define CS22               2
#define WGM21              3
#define COM20              4
#define COM21              5
#define WGM20              6
#define FOC2               7
#define TCNT2              *( (volatile u8*)0x44)
#define OCR2               *( (volatile u8*)0x43)
#define ASSR               *( (volatile u8*)0x42)
#define TCR2UB             0
#define OCR2UB             1
#define TCN2UB             2
#define AS2                3
#ifndef SFIOR
#define SFIOR              *( (volatile u8*)0x50)
#endif
#define PSR2               1
///////////////////////CONFIG MACROS/////////////////////////
#define ENABLE                                           1
#define DISABLE                                          0
#define NO_PRE                                           1
#define PRE_8                                            2
#define PRE_64                                           3
#define PRE_256                                          4
#define PRE_1024                                         5
#define EXT_FALLING                                      6
#define EXT_RISING                                       7
#define NORMAL                                           0x00
//TIMER0 macros
#define CTC                                              0x08
#define PWM_PHASE_CORRECT                                0x40
#define FAST_PWM                                         0x48
#define OC0_OFF                                          0
#define TGL_OC0                                          1
#define CLR_OC0                                          2
#define SET_OC0                                          3
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

#define OC1_OFF                                          0
#define TGL_OC1                                          1
#define CLR_OC1                                          2
#define SET_OC1                                          3


//TIMER2 macros
#define TM2_PWM_PHASE_CORRECT                            0x40
#define TM2_CTC                                          0x08
#define TM2_FAST_PWM                                     0x48
#define OC2_OFF                                          0
#define TGL_OC2                                          1
#define CLR_OC2                                          2
#define SET_OC2                                          3

#define TM2_PRE_32                                       3
#define TM2_PRE_64                                       4
#define TM2_PRE_128                                      5
#define TM2_PRE_256                                      6
#define TM2_PRE_1024                                     7


//TIMER ISRS
void __vector_4  (void) __attribute__ ((signal, used));
void __vector_5  (void) __attribute__ ((signal, used));
void __vector_6  (void) __attribute__ ((signal, used));
void __vector_7  (void) __attribute__ ((signal, used));
void __vector_8  (void) __attribute__ ((signal, used));
void __vector_9  (void) __attribute__ ((signal, used));
void __vector_10 (void) __attribute__ ((signal, used));
void __vector_11 (void) __attribute__ ((signal, used));

#ifndef F_CPU
#define F_CPU         8000000UL
#endif
///////////////Enable Or Disable Timers///////////////
#define TIMER_0			    ENABLE
#define TIMER_1			    ENABLE
#define TIMER_2			    DISABLE

/***************************************/
/*************TIMER0 CONFIG*************/
/***************************************/
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
///////////////CHOOSE FAST PWM MODE CONFIG////////////////
/*options in Compare Output Mode, Fast PWM Mode
OC0_OFF: Normal port operation, OC0 disconnected.
CLR_OC0: Clear OC0 on compare match, set OC0 at BOTTOM, (non-inverting mode)
SET_OC0: Set OC0 on compare match, clear OC0 at BOTTOM, (inverting mode)
*/
#define TIMER_0_FAST_PWM     CLR_OC0
///////////////CHOOSE Phase Correct PWM MODE CONFIG////////////////
/*options in Compare Output Mode,  Phase Correct PWM Mode
OC0_OFF: Normal port operation, OC0 disconnected.
CLR_OC0: Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting.
SET_OC0: Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting.
*/
#define TIMER_0_PHASE_PWM    CLR_OC0
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
/***************************************/
/*************TIMER1 CONFIG*************/
/***************************************/
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
///////////////CHOOSE FAST PWM MODE CONFIG FOR CH A & CH B////////////////
/*options in Compare Output Mode, Fast PWM Mode
OC1_OFF: Normal port operation, OC1A/OC1B disconnected.
TGL_OC1: FAST_PWM_OCR1A_TOP Mode: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation).
         For all other Modes, normal port operation, OC1A/OC1B disconnected.
CLR_OC1: Clear OC1A/OC1B on compare match when up-counting. Set OC1A/OC1B on compare match when down-counting.
SET_OC1: Set OC1A/OC1B on compare match when up-counting. Clear OC1A/OC1B on compare match when down-counting.
*/
#define TIMER_1_FAST_PWM_A    CLR_OC1
#define TIMER_1_FAST_PWM_B    CLR_OC1
///////////////CHOOSE Phase Correct PWM and Phase and Frequency Correct PWM MODE CONFIG FOR CH A & CH B////////////////
/*options in Compare Output Mode,  Phase Correct PWM Mode
OC1_OFF:  Normal port operation, OC1A/OC1B disconnected.
TGL_OC1: -PWM_PHASE_FREQ_CORRECT_OCR1A_TOP & FAST_PWM_ICR1_TOP Modes:
            Toggle OC1A on Compare Match, OC1B disconnected (normal port operation).
         -For all other Modes, normal port operation, OC1A/OC1B disconnected.
CLR_OC1: Clear OC1A/OC1B on compare match when up-counting. Set OC1A/OC1B on compare match when down-counting.
SET_OC1: Set OC1A/OC1B on compare match when up-counting. Clear OC1A/OC1B on compare match when down-counting.
*/
#define TIMER_1_PHASE_PWM_A   TGL_OC1
#define TIMER_1_PHASE_PWM_B   TGL_OC1
///////////////Enable OR Disable Input Capture Noise Canceler///////////////
//options: { ENABLE, DISABLE }
#define ICNC                  DISABLE
///////////////Choose Falling OR Rising Edge For Input Capture//////////////
//options: { TIMER_1_IC_FALLING, TIMER_1_IC_RISING }
#define IC_EDGE               TIMER_1_IC_FALLING
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
/***************************************/
/*************TIMER2 CONFIG*************/
/***************************************/
///////////////CHOOSE MODE OF OPERATION///////////////
/* Timer/Counter Mode of Operation | TOP | Update of OCR0 | TOV0 Flag Set-on
-----------------------------------|-----|----------------|-----------------
           TM2_NORMAL              |0xFF |    Immediate   |      MAX
           TM2_PWM_PHASE_CORRECT   |0xFF |       TOP      |     BOTTOM
           TM2_CTC                 |OCR2 |    Immediate   |      MAX
           TM2_FAST_PWM            |0xFF |     BOTTOM     |      MAX
*/
#define TIMER_2_MODE         TM2_FAST_PWM
///////////////CHOOSE NORMAL/CTC MODE CONFIG///////////////
/*options in Compare Output Mode, non-PWM Mode
OC2_OFF: Normal port operation, OC2 disconnected.
TGL_OC2: Toggle OC2 on compare match
CLR_OC2: Clear OC2 on compare match
SET_OC2: Set OC2 on compare match
*/
#define TIMER_2_NORMAL       TGL_OC2
///////////////CHOOSE FAST PWM MODE CONFIG////////////////
/*options in Compare Output Mode, Fast PWM Mode
OC2_OFF: Normal port operation, OC2 disconnected.
CLR_OC2: Clear OC2 on compare match, set OC0 at BOTTOM, (non-inverting mode)
SET_OC2: Set OC2 on compare match, clear OC0 at BOTTOM, (inverting mode)
*/
#define TIMER_2_FAST_PWM     CLR_OC2
///////////////CHOOSE Phase Correct PWM MODE CONFIG////////////////
/*options in Compare Output Mode,  Phase Correct PWM Mode
OC2_OFF: Normal port operation, OC2 disconnected.
CLR_OC2: Clear OC2 on compare match when up-counting. Set OC2 on compare match when down-counting.
SET_OC2: Set OC2 on compare match when up-counting. Clear OC0 on compare match when down-counting.
*/
#define TIMER_2_PHASE_PWM    CLR_OC2
///////////////CHOOSE TIMER0 CLOCK SOURCE///////////////
/*options       :
NO_PRE          : F_CPU (No prescaling)
PRE_8           : F_CPU / 8 (From prescaler)
TM2_PRE_32      : F_CPU / 32 (From prescaler)
TM2_PRE_64      : F_CPU / 64 (From prescaler)
TM2_PRE_128     : F_CPU / 128 (From prescaler)
TM2_PRE_256     : F_CPU / 256 (From prescaler)
TM2_PRE_1024    : F_CPU / 1024 (From prescaler)
*/
#define TIMER_2_CLK           TM2_PRE_1024
///////////////ENABLE TIMER2 INTERRUPTS///////////////
#define TIMER_2_OC_INTERRUPT  DISABLE
#define TIMER_2_OVF_INTERRUPT DISABLE


//driver interfacing macros
#define    TIMER_TM0			0
#define    TIMER_TM1			1
#define    TIMER_TM2			2

#define    TIMER_TM1_ICR	    3
#define    TIMER_TM1_CH_A       4
#define    TIMER_TM1_CH_B	    5

#define    TIMER_1_IC_FALLING   0
#define    TIMER_1_IC_RISING    1
//TIMERS INTERRUPTS
#define    TIMER2_COMP          0
#define    TIMER2_OVF           1
#define    TIMER1_CAPT          2
#define    TIMER1_COMPA         3
#define    TIMER1_COMPB         4
#define    TIMER1_OVF           5
#define    TIMER0_COMP          6
#define    TIMER0_OVF           7
typedef enum en_timerError{
	TIMER_OK,
	TIMER_WRONG_INPUT,
	TIMER_NOK
	}en_timerError;
/***
 * initializes TIMERS based on the selected config, returns void
 * INPUT: void
 * OUTPUT: void
 * Returns: void
 * **/
en_timerError TIMER_init(void);
/***
 * Starts a specific TIMER based on input, returns void
 * INPUT: (u8) Timer to start
 * OUTPUT: void
 * Returns: void
 * **/
en_timerError TIMER_start(u8 u8_a_timerNumber);
/***
 * Stops a specific TIMER based on input, returns void
 * INPUT: (u8) Timer to stop
 * OUTPUT: void
 * Returns: void
 * **/
en_timerError TIMER_stop(u8 u8_a_timerNumber);
/***
 * Reads a specific TIMER's current value(counter register) based on input, returns void
 * INPUT: (u8) Timer to read, (u16*) pointer to store the value
 * OUTPUT: (u16) timer current value
 * Returns: void
 * **/
en_timerError TIMER_read(u8 u8_a_timerNumber, u16* u16_a_tTimerValue);
/***
 * Preloads a specific TIMER value(counter register) based on input, returns void
 * INPUT:(u16) preload value , (u8) Timer to preload
 * OUTPUT: void
 * Returns: void
 * **/
en_timerError TIMER_preload(u16 u16_a_value, u8 u8_a_timerNumber);
/***
 * Loads a specific TIMER value(compare register) based on input, returns void
 * INPUT:(u16) load value , (u8) Timer to load
 * OUTPUT: void
 * Returns: void
 * **/
en_timerError TIMER_load(u16 u16_a_value, u8 u8_a_timerNumber);
/***
 * Generates a non-pwm signal from a specific TIMER based on input, returns void
 * INPUT: (u8) Timer to generate signal from
 * OUTPUT: void
 * Returns: void
 * **/
en_timerError TIMER_generateNonPwmSignal(u8 u8_a_timerNumber);
/***
 * Generates a fast pwm signal from a specific TIMER based on input, returns void
 * INPUT: (u8) Timer to generate signal from
 * OUTPUT: void
 * Returns: void
 * **/
en_timerError TIMER_generateFastPwmSignal(u8 u8_a_timerNumber);
/***
 * Generates a phase correct pwm signal from a specific TIMER based on input, returns void
 * INPUT: (u8) Timer to generate signal from
 * OUTPUT: void
 * Returns: void
 * **/
en_timerError TIMER_generatePhasePwmSignal(u8 u8_a_timerNumber);
/***
 * Specifies the working edge of timer1's input capture unit, returns void
 * INPUT: (u8) Wanted edge
 * OUTPUT: void
 * Returns: void
 * **/
en_timerError TIMER_setICUEdge(u8 u8_a_icEDGE);
/***
 * Reads the value of timer1's input capture unit, returns void
 * INPUT: (u16*) Pointer to store the read value
 * OUTPUT: (u16) captured value
 * Returns: void
 * **/
en_timerError TIMER_getICU(u16 *u16_a_value);
/***
 * Sets the callback function for the input timer interrupt, returns void
 * INPUT: (u8) timer interrupt name, (*ptr) call back function
 * OUTPUT: void
 * Returns: void
 * **/
en_timerError TIMER_setCallBack(u8 u8_a_timerInterruptNum, void (*v_a_ptr)(void));
/***
 * Reads the value of the input frequency & pulse width from the ICU, returns void
 * INPUT: (u16*) Pointer to store frequency, (u16*) Pointer to store pulse width
 * OUTPUT: (u16) signal frequency, (u16) signal TimeOn
 * Returns: void
 * **/
en_timerError TIMER_measureSignal(u32 *u16_a_frequency, u32 *u16_a_timeOn);




#endif /* TIMER_H_ */