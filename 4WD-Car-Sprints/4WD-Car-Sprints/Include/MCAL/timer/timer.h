

#ifndef TIMER_H_
#define TIMER_H_

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

/***
 * initializes TIMERS based on the selected config, returns void
 * INPUT: void
 * OUTPUT: void
 * Returns: void
 * **/
u8_returnType TIMER_init(void);
/***
 * Starts a specific TIMER based on input, returns void
 * INPUT: (u8) Timer to start
 * OUTPUT: void
 * Returns: void
 * **/
u8_returnType TIMER_start(u8 u8cpyTimerNumber);
/***
 * Stops a specific TIMER based on input, returns void
 * INPUT: (u8) Timer to stop
 * OUTPUT: void
 * Returns: void
 * **/
u8_returnType TIMER_stop(u8 u8cpyTimerNumber);
/***
 * Reads a specific TIMER's current value(counter register) based on input, returns void
 * INPUT: (u8) Timer to read, (u16*) pointer to store the value
 * OUTPUT: (u16) timer current value
 * Returns: void
 * **/
u8_returnType TIMER_read(u8 u8cpyTimerNumber, u16* u16TimerValue);
/***
 * Preloads a specific TIMER value(counter register) based on input, returns void
 * INPUT:(u16) preload value , (u8) Timer to preload
 * OUTPUT: void
 * Returns: void
 * **/
u8_returnType TIMER_preload(u16 u16cpyValue, u8 u8cpyTimerNumber);
/***
 * Loads a specific TIMER value(compare register) based on input, returns void
 * INPUT:(u16) load value , (u8) Timer to load
 * OUTPUT: void
 * Returns: void
 * **/
u8_returnType TIMER_load(u16 u16cpyValue, u8 u8cpyTimerNumber);
/***
 * Generates a non-pwm signal from a specific TIMER based on input, returns void
 * INPUT: (u8) Timer to generate signal from
 * OUTPUT: void
 * Returns: void
 * **/
u8_returnType TIMER_generateNonPwmSignal(u8 u8cpyTimerNumber);
/***
 * Generates a fast pwm signal from a specific TIMER based on input, returns void
 * INPUT: (u8) Timer to generate signal from
 * OUTPUT: void
 * Returns: void
 * **/
u8_returnType TIMER_generateFastPwmSignal(u8 u8cpyTimerNumber);
/***
 * Generates a phase correct pwm signal from a specific TIMER based on input, returns void
 * INPUT: (u8) Timer to generate signal from
 * OUTPUT: void
 * Returns: void
 * **/
u8_returnType TIMER_generatePhasePwmSignal(u8 u8cpyTimerNumber);
/***
 * Specifies the working edge of timer1's input capture unit, returns void
 * INPUT: (u8) Wanted edge
 * OUTPUT: void
 * Returns: void
 * **/
u8_returnType TIMER_setICUEdge(u8 u8cpyIC_EDGE);
/***
 * Reads the value of timer1's input capture unit, returns void
 * INPUT: (u16*) Pointer to store the read value
 * OUTPUT: (u16) captured value
 * Returns: void
 * **/
u8_returnType TIMER_getICU(u16 *u8cpy_Value);
/***
 * Sets the callback function for the input timer interrupt, returns void
 * INPUT: (u8) timer interrupt name, (*ptr) call back function
 * OUTPUT: void
 * Returns: void
 * **/
u8_returnType TIMER_setCallBack(ut8 u8cpyTimerInterruptNum, void (*ptr)(void));
/***
 * Reads the value of the input frequency & pulse width from the ICU, returns void
 * INPUT: (u16*) Pointer to store frequency, (u16*) Pointer to store pulse width
 * OUTPUT: (u16) signal frequency, (u16) signal TimeOn
 * Returns: void
 * **/
u8_returnType TIMER_measureSignal(u32 *u16cpy_frequency, u32 *u16cpy_timeOn);




#endif /* TIMER_H_ */