/*
* timer.c
*
* Created: 10/3/2023 2:09:50 PM
*  Author: melgreatly
*/
#include "../../00 LIB/STD_TYPES.h"
#include "../../00 LIB/BIT_MATH.h"
#include "timer.h"

void (*v_g_callbackFunc[8])(void) = { NULL };

u8_returnType TIMER_init(void) {
	u8_returnType u8_a_retFunction = E_OK;
	TIMSK = 0x00;
	TIFR = 0x00;
	TIMSK = (TIMER_0_OC_INTERRUPT << OCIE0) | (TIMER_0_OVF_INTERRUPT << TOIE0)
	| (TIMER_1_IC_INTERRUPT << TICIE1)
	| (TIMER_1_OCA_INTERRUPT << OCIE1A)
	| (TIMER_1_OCB_INTERRUPT << OCIE1B)
	| (TIMER_1_OVF_INTERRUPT << TOIE1) | (TIMER_2_OC_INTERRUPT << OCIE2)
	| (TIMER_2_OVF_INTERRUPT << TOIE2);
	#if TIMER_0 == ENABLE
	TCCR0 = ((TCCR0 & 0x00) | TIMER_0_MODE);
	TCNT0 = 0x00;
	OCR0 = 0x00;
	#endif
	#if TIMER_1 == ENABLE
	TCCR1A = ((TCCR1A & 0x00) | (TIMER_1_MODE & 0x03));
	TCCR1B = ((TCCR1B & 0x00) | ((TIMER_1_MODE >> 2) << WGM12)
	| (IC_EDGE << ICES1) | (ICNC << ICNC1));
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	OCR1AH = 0x00;
	OCR1AL = 0x00;
	OCR1BH = 0x00;
	OCR1BL = 0x00;
	ICR1H = 0x00;
	ICR1L = 0x00;
	#endif
	#if TIMER_2 == ENABLE
	TCCR2 = ((TCCR2 & 0x00) | TIMER_2_MODE);
	TCNT2 = 0x00;
	OCR2 = 0x00;
	ASSR = 0x00;
	#endif
	return u8_a_retFunction;
}
u8_returnType TIMER_start(u8 u8_a_timerNumber) {
	u8_returnType u8_a_retFunction = E_OK;
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
			case TIMER_TM2:
			TCCR2 |= (TIMER_2_CLK << CS20);
			break;
		}
		} else {
		u8_a_retFunction = E_NOK;
	}
	return u8_a_retFunction;
}
u8_returnType TIMER_stop(u8 u8_a_timerNumber) {
	u8_returnType u8_a_retFunction = E_OK;
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
			case TIMER_TM2:
			TCCR2 &= 0xF8;
			break;
		}
		} else {
		u8_a_retFunction = E_NOK;
	}
	return u8_a_retFunction;
}
u8_returnType TIMER_read(u8 u8_a_timerNumber, u16* u16_a_tTimerValue) {
	u8_returnType u8_a_retFunction = E_OK;
	if(u8_a_timerNumber < 3 && u16_a_tTimerValue != NULL){
		switch (u8_a_timerNumber) {
			case TIMER_TM0:
			*u16_a_tTimerValue = TCNT0;
			break;
			case TIMER_TM1:
			*u16_a_tTimerValue = (TCNT1L | (TCNT1H << 8));
			break;
			case TIMER_TM2:
			*u16_a_tTimerValue = TCNT2;
			break;
		}
		} else {
		u8_a_retFunction = E_NOK;
	}
	return u8_a_retFunction;
}
u8_returnType TIMER_preload(u16 u16_a_value, u8 u8_a_timerNumber) {
	u8_returnType u8_a_retFunction = E_OK;
	if(u8_a_timerNumber < 3 && u16_a_value != NULL){
		switch (u8_a_timerNumber) {
			case TIMER_TM0:
			TCNT0 = (u8) u16_a_value;
			break;
			case TIMER_TM1:
			TCNT1H = (u8) (u16_a_value >> 8);
			TCNT1L = (u8) u16_a_value;
			break;
			case TIMER_TM2:
			TCNT2 = (u8) u16_a_value;
			break;
		}
		} else {
		u8_a_retFunction = E_NOK;
	}
	return u8_a_retFunction;
}
u8_returnType TIMER_load(u16 u16_a_value, u8 u8_a_timerNumber) {
	u8_returnType u8_a_retFunction = E_OK;
	if(u8_a_timerNumber < 3 && u16_a_value != NULL){
		switch (u8_a_timerNumber) {
			case TIMER_TM0:
			OCR0 = (u8) u16_a_value;
			break;
			case TIMER_TM1_ICR:
			ICR1H = (u8) (u16_a_value >> 8);
			ICR1L = (u8) u16_a_value;
			break;
			case TIMER_TM1_CH_A:
			OCR1AH = (u8) (u16_a_value >> 8);
			OCR1AL = (u8) u16_a_value;
			break;
			case TIMER_TM1_CH_B:
			OCR1BH = (u8) (u16_a_value >> 8);
			OCR1BL = (u8) u16_a_value;
			break;
			case TIMER_TM2:
			OCR2 = (u8) u16_a_value;
			break;
		}
		} else {
		u8_a_retFunction = E_NOK;
	}
	return u8_a_retFunction;
}
u8_returnType TIMER_generateNonPwmSignal(u8 u8_a_timerNumber) {
	u8_returnType u8_a_retFunction = E_OK;
	if(u8_a_timerNumber < 3){
		switch (u8_a_timerNumber) {
			case TIMER_TM0:
			TCCR0 = ((TCCR0 & 0xCF) | (TIMER_0_NORMAL << COM00));
			break;
			case TIMER_TM1_CH_A:
			TCCR1A = ((TCCR1A & 0x3F) | (TIMER_1_NORMAL_A << COM1A0));
			break;
			case TIMER_TM1_CH_B:
			TCCR1A = ((TCCR1A & 0xCF) | (TIMER_1_NORMAL_B << COM1B0));
			break;
			case TIMER_TM2:
			TCCR2 = ((TCCR2 & 0xCF) | (TIMER_2_NORMAL << COM20));
			break;
		}
		} else {
		u8_a_retFunction = E_NOK;
	}
	return u8_a_retFunction;
}
u8_returnType TIMER_generateFastPwmSignal(u8 u8_a_timerNumber) {
	u8_returnType u8_a_retFunction = E_OK;
	if(u8_a_timerNumber < 3){
		switch (u8_a_timerNumber) {
			case TIMER_TM0:
			TCCR0 = ((TCCR0 & 0xCF) | (TIMER_0_FAST_PWM << COM00));
			break;
			case TIMER_TM1_CH_A:
			TCCR1A = ((TCCR1A & 0x3F) | (TIMER_1_FAST_PWM_A << COM1A0));
			break;
			case TIMER_TM1_CH_B:
			TCCR1A = ((TCCR1A & 0xCF) | (TIMER_1_FAST_PWM_B << COM1B0));
			break;
			case TIMER_TM2:
			TCCR2 = ((TCCR2 & 0xCF) | (TIMER_2_FAST_PWM << COM20));
			break;
		}
		} else {
		u8_a_retFunction = E_NOK;
	}
	return u8_a_retFunction;
}
u8_returnType TIMER_generatePhasePwmSignal(u8 u8_a_timerNumber) {
	u8_returnType u8_a_retFunction = E_OK;
	if(u8_a_timerNumber < 3){
		switch (u8_a_timerNumber) {
			case TIMER_TM0:
			TCCR0 = ((TCCR0 & 0xCF) | (TIMER_0_PHASE_PWM << COM00));
			break;
			case TIMER_TM1_CH_A:
			TCCR1A = ((TCCR1A & 0x3F) | (TIMER_1_PHASE_PWM_A << COM1A0));
			break;
			case TIMER_TM1_CH_B:
			TCCR1A = ((TCCR1A & 0xCF) | (TIMER_1_PHASE_PWM_B << COM1B0));
			break;
			case TIMER_TM2:
			TCCR2 = ((TCCR2 & 0xCF) | (TIMER_2_PHASE_PWM << COM20));
			break;
		}
		} else {
		u8_a_retFunction = E_NOK;
	}
	return u8_a_retFunction;
}
u8_returnType TIMER_setCallBack(u8 u8_a_timerInterruptNum, void (*v_a_ptr)(void)) {
	u8_returnType u8_a_retFunction = E_OK;
	if ( NULL == v_a_ptr)
	{
		u8_a_retFunction = E_NOK;
	}
	else
	{
		if (u8_a_timerInterruptNum >= 0 && u8_a_timerInterruptNum < 8) 
		{
			ptr_func[u8_a_timerInterruptNum] = v_a_ptr;
		} 
		else {
			u8_a_retFunction = E_NOK;
		}
	}
	return u8_a_retFunction ;
}

u8_returnType TIMER_setICUEdge(u8 u8_a_icEDGE) {
	
	u8_returnType u8_a_retFunction = E_OK;
	if (u8_a_icEDGE != TIMER_1_IC_FALLING && u8_a_icEDGE != TIMER_1_IC_RISING)
	{
		u8_a_retFunction = E_NOK;
	}
	else
	{
		TCCR1B = (TCCR1B & 0x9F) | (u8_a_icEDGE << ICES1);
		SET_BIT(TIFR, ICF1);
	}
	return u8_a_retFunction;
	
}
u8_returnType TIMER_getICU(u16 *u16_a_value) {
	u8_returnType u8_a_retFunction = E_OK;
	if(u16_a_value != NULL){
		*u16_a_value = ((u16) ICR1L | ((u16) ICR1H << 8));
		} else {
		u8_a_retFunction = E_NOK;
	}
	return u8_a_retFunction;
}
u8_returnType TIMER_measureSignal(u32 *u16_a_frequency, u32 *u16_a_timeOn) {
	u8_returnType u8_a_retFunction = E_OK;
	u16 Ticks[3] = { 0 };
	u16 Period = 0;
	u16 Ton = 0;
	if (NULL == u16_a_frequency || NULL == u16_a_timeOn )
	{
		u8_a_retFunction = E_NOK;
	}
	else
	{
			SET_BIT(TIFR, ICF1);
			TIMER_start(TIMER_TM1);
			while (!(TIFR & (1 << ICF1)))
			;
			TIMER_getICU(&Ticks[0]);
			TIMER_setICUEdge(TIMER_1_IC_RISING);
			while (!(TIFR & (1 << ICF1)))
			;
			TIMER_getICU(&Ticks[1]);
			TIMER_setICUEdge(TIMER_1_IC_FALLING);
			while (!(TIFR & (1 << ICF1)))
			;
			TIMER_getICU(&Ticks[2]);
			if (Ticks[2] > Ticks[1]) {
				Period = Ticks[2] - Ticks[0];
				} else if (Ticks[2] < Ticks[1]) {
				Period = (0xffff - Ticks[0]) + Ticks[2];
			}
			if (Ticks[2] > Ticks[1]) {
				Ton = Ticks[2] - Ticks[1];
				} else if (Ticks[2] < Ticks[1]) {
				Ton = (0xffff - Ticks[1]) + Ticks[2];
			}
			TIMER_stop(TIMER_TM1);
			u32 prescaler = 0;
			#if TIMER_1_CLK == PRE_8
			prescaler = 8;
			#elif TIMER_1_CLK == NO_PRE
			prescaler = 1;
			#elif TIMER_1_CLK == PRE_64PRE_8
			prescaler = 64;
			#elif TIMER_1_CLK == PRE_256
			prescaler = 256;
			#elif TIMER_1_CLK == PRE_1024
			prescaler = 1024;
			#endif
			*u16_a_frequency =  (u16) ((d64)((d64)F_CPU / (d64)prescaler)   / (d64) Period);
			*u16_a_timeOn = (u16) ( ( (d64)prescaler / (d64)((d64)F_CPU / 1000000.0) ) * Ton);
	}
	return u8_a_retFunction;
}
void __vector_4(void) {
	if (v_g_callbackFunc[TIMER2_COMP] != NULL)
	v_g_callbackFunc[TIMER2_COMP]();
}
void __vector_5(void) {
	if (v_g_callbackFunc[TIMER2_OVF] != NULL)
	v_g_callbackFunc[TIMER2_OVF]();
}
void __vector_6(void) {
	if (v_g_callbackFunc[TIMER1_CAPT] != NULL)
	v_g_callbackFunc[TIMER1_CAPT]();

}
void __vector_7(void) {
	if (v_g_callbackFunc[TIMER1_COMPA] != NULL)
	v_g_callbackFunc[TIMER1_COMPA]();
}
void __vector_8(void) {
	if (v_g_callbackFunc[TIMER1_COMPB] != NULL)
	v_g_callbackFunc[TIMER1_COMPB]();
}
void __vector_9(void) {
	if (v_g_callbackFunc[TIMER1_OVF] != NULL)
	v_g_callbackFunc[TIMER1_OVF]();
}
void __vector_10(void) {
	if (v_g_callbackFunc[TIMER0_COMP] != NULL)
	v_g_callbackFunc[TIMER0_COMP]();
}
void __vector_11(void) {
	if (v_g_callbackFunc[TIMER0_OVF] != NULL)
	v_g_callbackFunc[TIMER0_OVF]();
}