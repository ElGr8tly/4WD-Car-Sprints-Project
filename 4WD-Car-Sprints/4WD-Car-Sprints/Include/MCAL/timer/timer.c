/*
* timer.c
*
* Created: 10/3/2023 2:09:50 PM
*  Author: melgreatly
*/
#include "../../00 LIB/STD_TYPES.h"
#include "../../00 LIB/BIT_MATH.h"
#include "timer.h"

void (*ptr_func[8])(void) = { NULL };

u8_returnType TIMER_init(void) {
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

}
u8_returnType TIMER_start(u8 u8_a_timerNumber) {
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

}
u8_returnType TIMER_stop(u8 u8_a_timerNumber) {
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
}
u8_returnType TIMER_read(u8 u8_a_timerNumber, u16* u16_a_tTimerValue) {
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
}
u8_returnType TIMER_preload(u16 u16_a_value, u8 u8_a_timerNumber) {
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
}
u8_returnType TIMER_load(u16 u16_a_value, u8 u8_a_timerNumber) {
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
}
u8_returnType TIMER_generateNonPwmSignal(u8 u8_a_timerNumber) {
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
}
u8_returnType TIMER_generateFastPwmSignal(u8 u8_a_timerNumber) {
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
}
void MTIMER_voidGeneratePhasePwmSignal(u8 u8cpyTimerNumber) {
	switch (u8cpyTimerNumber) {
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
}
void MTIMER_voidSetCallBack(u8 u8cpyTimerInterruptNum, void (*ptr)(void)) {
	if (u8cpyTimerInterruptNum >= 0 && u8cpyTimerInterruptNum < 8) {
		ptr_func[u8cpyTimerInterruptNum] = ptr;
		} else {
		//input error
	}
}

void MTIMER_voidSetICUEdge(u8 u8cpyIC_EDGE) {
	//Clr_Bit(TIMSK, TICIE1);
	TCCR1B = (TCCR1B & 0x9F) | (u8cpyIC_EDGE << ICES1);
	Set_Bit(TIFR, ICF1);
	//Set_Bit(TIMSK, TICIE1);
}
void MTIMER_voidGetICU(u16 *u8cpy_Value) {
	*u8cpy_Value = ((u16) ICR1L | ((u16) ICR1H << 8));
}
void MTIMER_voidMeasureSignal(u32 *u16cpy_frequency, u32 *u16cpy_timeOn) {
	u16 Ticks[3] = { 0 };
	u16 Period = 0;
	u16 Ton = 0;
	Set_Bit(TIFR, ICF1);
	MTIMER_voidStart(TIMER_TM1);
	while (!(TIFR & (1 << ICF1)))
	;
	MTIMER_voidGetICU(&Ticks[0]);
	MTIMER_voidSetICUEdge(TIMER_1_IC_RISING);
	while (!(TIFR & (1 << ICF1)))
	;
	MTIMER_voidGetICU(&Ticks[1]);
	MTIMER_voidSetICUEdge(TIMER_1_IC_FALLING);
	while (!(TIFR & (1 << ICF1)))
	;
	MTIMER_voidGetICU(&Ticks[2]);
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
	MTIMER_voidStop(TIMER_TM1);
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
	*u16cpy_frequency =  (u16) ((f64)((f64)F_CPU / (f64)prescaler)   / (f64) Period);
	*u16cpy_timeOn = (u16) ( ( (f64)prescaler / (f64)((f64)F_CPU / 1000000.0) ) * Ton);
}
void __vector_4(void) {
	if (ptr_func[TIMER2_COMP] != NULL)
	ptr_func[TIMER2_COMP]();
}
void __vector_5(void) {
	if (ptr_func[TIMER2_OVF] != NULL)
	ptr_func[TIMER2_OVF]();
}
void __vector_6(void) {
	if (ptr_func[TIMER1_CAPT] != NULL)
	ptr_func[TIMER1_CAPT]();

}
void __vector_7(void) {
	if (ptr_func[TIMER1_COMPA] != NULL)
	ptr_func[TIMER1_COMPA]();
}
void __vector_8(void) {
	if (ptr_func[TIMER1_COMPB] != NULL)
	ptr_func[TIMER1_COMPB]();
}
void __vector_9(void) {
	if (ptr_func[TIMER1_OVF] != NULL)
	ptr_func[TIMER1_OVF]();
}
void __vector_10(void) {
	if (ptr_func[TIMER0_COMP] != NULL)
	ptr_func[TIMER0_COMP]();
}
void __vector_11(void) {
	if (ptr_func[TIMER0_OVF] != NULL)
	ptr_func[TIMER0_OVF]();
}