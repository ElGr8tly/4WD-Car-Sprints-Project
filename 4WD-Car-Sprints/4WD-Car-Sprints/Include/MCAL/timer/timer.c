/******************************************************************************************************************
    Author 		    : Mahmoud Mahran
	Version		    : V:1.0
	Date 		    : 03/10/2023
    Description     : timer.c  ->  Implementation
  
    Module features :

						01- TIMER_init
						02- TIMER_start
						03- TIMER_stop
						04- TIMER_read
						05- TIMER_preload
						06- TIMER_setCallBack
						
*/


/*
************************************************************************************************************************
											Standard Types
************************************************************************************************************************
*/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


/*
************************************************************************************************************************
											MCAL Components
************************************************************************************************************************
*/
#include "timer.h"

/*
************************************************************************************************************************
************************************************************************************************************************
************************************************************************************************************************
*/

///////////////////////////////////Function pointers array to handle callbacks//////////////////////////////////////////////
static void (*v_g_callbackFunc[2])(void) = { NULL };
	
/*
************************************************************************************************************************
											Functions Implementation
************************************************************************************************************************
*/




/*
**************************************************************************************************************************
********************************************** 01 - TIMER_init  **********************************************************

	1-  function Description ->  initializes TIMERS based on the selected config, returns void
	2-  Options : NA
				  
	3- Function Arguments : void
	
	4- Function Return   ->  void
	
**************************************************************************************************************************
**************************************************************************************************************************	
*/

en_timerError TIMER_init(void) {
	en_timerError en_a_retFunction = TIMER_OK;
	TIMSK = 0x00;
	TIFR  = 0x00;
	TIMSK = (TIMER_0_OC_INTERRUPT << OCIE0) | (TIMER_0_OVF_INTERRUPT << TOIE0)
	| (TIMER_1_IC_INTERRUPT << TICIE1)
	| (TIMER_1_OCA_INTERRUPT << OCIE1A)
	| (TIMER_1_OCB_INTERRUPT << OCIE1B)
	| (TIMER_1_OVF_INTERRUPT << TOIE1);
	#if TIMER_0 == ENABLE
	TCCR0 = ((TCCR0 & 0x00) | TIMER_0_MODE);
	TCNT0 = 0x00;
	OCR0 = 0x00;
	#endif
	#if TIMER_1 == ENABLE
	TCCR1A = ((TCCR1A & 0x00) | (TIMER_1_MODE & 0x03));
	TCCR1B = ((TCCR1B & 0x00) | ((TIMER_1_MODE >> 2) << WGM12));
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	OCR1AH = 0x00;
	OCR1AL = 0x00;
	OCR1BH = 0x00;
	OCR1BL = 0x00;
	ICR1H  = 0x00;
	ICR1L  = 0x00;
	#endif
	return en_a_retFunction;
}
/*
**************************************************************************************************************************
********************************************** 02 - TIMER_start  **********************************************************

	1-  function Description ->  Starts a specific TIMER based on input, returns void
	2-  Options :           (A) TIMER0
	                        (B) TIMER1
				  
	3- Function Arguments : (u8) Timer to start (ex : TIMER_TM0 , TIMER_TM1..)
	
	4- Function Return   ->  (en_timerError)    (ex : TIMER_OK , TIMER_WRONG_INPUT..)
	
**************************************************************************************************************************
**************************************************************************************************************************	
*/
en_timerError TIMER_start(u8 u8_a_timerNumber) {
	en_timerError en_a_retFunction = TIMER_OK;
	if(u8_a_timerNumber < 3){
		switch (u8_a_timerNumber) {
			case TIMER_TM0:
			TCCR0 |= (TIMER_0_CLK << CS00);
			break;
			case TIMER_TM1:
			TCNT1H = 0x00;
			TCNT1L = 0x00;
			TCCR1B |= (TIMER_1_CLK << CS10);
			break;
		}
		} else {
		en_a_retFunction = TIMER_WRONG_INPUT;
	}
	return en_a_retFunction;
}
/*
**************************************************************************************************************************
********************************************** 03 - TIMER_stop  **********************************************************

	1-  function Description ->  Stops a specific TIMER based on input, returns void
	2-  Options :           (A) TIMER0
	                        (B) TIMER1
				  
	3- Function Arguments : (u8) Timer to stop (ex : TIMER_TM0 , TIMER_TM1..)
	
	4- Function Return   ->  (en_timerError)   (ex : TIMER_OK , TIMER_WRONG_INPUT..)
	
**************************************************************************************************************************
**************************************************************************************************************************	
*/
en_timerError TIMER_stop(u8 u8_a_timerNumber) {
	en_timerError en_a_retFunction = TIMER_OK;
	if(u8_a_timerNumber < 3){
		switch (u8_a_timerNumber) {
			case TIMER_TM0:
			TCCR0 &= 0xF8;
			break;
			case TIMER_TM1:
			TCCR1B &= 0xF8;
			TCNT1H = 0x00;
			TCNT1L = 0x00;
			break;
		}
		} else {
		en_a_retFunction = TIMER_WRONG_INPUT;
	}
	return en_a_retFunction;
}
/*
**************************************************************************************************************************
********************************************** 04 - TIMER_read  **********************************************************

	1-  function Description ->  Reads a specific TIMER's current value(counter register) based on input, returns void
	2-  Options :           (A) TIMER0
	                        (B) TIMER1
				  
	3- Function Arguments : (u8) Timer to stop (ex : TIMER_TM0 , TIMER_TM1..)
	                        (u16*) var to store the value
	
	4- Function Return   ->  (en_timerError)    (ex : TIMER_OK , TIMER_WRONG_INPUT..)
	
**************************************************************************************************************************
**************************************************************************************************************************	
*/
en_timerError TIMER_read(u8 u8_a_timerNumber, u16* u16_a_tTimerValue) {
	en_timerError en_a_retFunction = TIMER_OK;
	if(u8_a_timerNumber < 3 && u16_a_tTimerValue != NULL){
		switch (u8_a_timerNumber) {
			case TIMER_TM0:
			*u16_a_tTimerValue = TCNT0;
			break;
			case TIMER_TM1:
			*u16_a_tTimerValue = (TCNT1L | (TCNT1H << 8));
			break;
		}
		} else {
		en_a_retFunction = TIMER_WRONG_INPUT;
	}
	return en_a_retFunction;
}
/*
**************************************************************************************************************************
********************************************** 05 - TIMER_preload  **********************************************************

	1-  function Description ->  Preloads a specific TIMER value(counter register) based on input, returns void
	2-  Options :           (A) TIMER0
	                        (B) TIMER1
				  
	3- Function Arguments : (u16) Preload value
	                        (u8)  Timer to preload (ex : TIMER_TM0 , TIMER_TM1..)
	
	4- Function Return   ->  (en_timerError)       (ex : TIMER_OK , TIMER_WRONG_INPUT..)
	
**************************************************************************************************************************
**************************************************************************************************************************	
*/
en_timerError TIMER_preload(u16 u16_a_value, u8 u8_a_timerNumber) {
	en_timerError en_a_retFunction = TIMER_OK;
	if(u8_a_timerNumber < 3){
		switch (u8_a_timerNumber) {
			case TIMER_TM0:
			TCNT0 = (u8) u16_a_value;
			break;
			case TIMER_TM1:
			TCNT1H = (u8) (u16_a_value >> 8);
			TCNT1L = (u8) u16_a_value;
			break;
		}
		} else {
		en_a_retFunction = TIMER_WRONG_INPUT;
	}
	return en_a_retFunction;
}
/*
**************************************************************************************************************************
****************************************** 06 - TIMER_setCallBack  *******************************************************

	1-  function Description ->  Sets the callback function for the input timer interrupt, returns void
	2-  Options :           (A) TIMER1 overflow
	                        (B) TIMER0 overflow
				  
	3- Function Arguments : (u8)  Timer interrupt name          (ex : TIMER1_OVF , TIMER0_OVF..)
	                        (*ptr) call back function          
	
	4- Function Return   ->  (en_timerError)       (ex : TIMER_OK , TIMER_WRONG_INPUT..)
	
**************************************************************************************************************************
**************************************************************************************************************************	
*/
en_timerError TIMER_setCallBack(u8 u8_a_timerInterruptNum, void (*v_a_ptr)(void)) {
	en_timerError en_a_retFunction = TIMER_OK;
	if ( NULL == v_a_ptr)
	{
		en_a_retFunction = TIMER_WRONG_INPUT;
	}
	else
	{
		if (u8_a_timerInterruptNum >= 0 && u8_a_timerInterruptNum < 2) 
		{
			v_g_callbackFunc[u8_a_timerInterruptNum] = v_a_ptr;
		} 
		else {
			en_a_retFunction = TIMER_WRONG_INPUT;
		}
	}
	return en_a_retFunction ;
}

/****************************************************************************************************/
//TIMER interrupt vectors(ISR Handlers)
void __vector_9(void) {
	if (v_g_callbackFunc[TIMER1_OVF] != NULL)
	v_g_callbackFunc[TIMER1_OVF]();
}
void __vector_11(void) {
	if (v_g_callbackFunc[TIMER0_OVF] != NULL)
	v_g_callbackFunc[TIMER0_OVF]();
}