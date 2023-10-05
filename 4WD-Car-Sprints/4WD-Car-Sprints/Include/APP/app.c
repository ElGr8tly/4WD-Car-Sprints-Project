/*
* app.c
*
* Created: 10/3/2023 2:11:11 PM
*  Author:
*/
#include "app.h"

en_systemStatus en_g_carStatus = SYSTEM_OFF;

u8 u8_g_sequenceNumber = 0;

u8 u8_g_halfSecondStop = 0;

extern u8 u8_g_pwmDutyCycle;

st_carMode st_g_systemSequence[SEQUENCE_MAX_NUMBER] = {
	{
		.ptr_g_Function = APP_longestSide,
		.period = LONGEST_SIDE_PERIOD
	},
	{
		.ptr_g_Function = APP_rotate,
		.period = ROTATE_PERIOD
	},
	{
		.ptr_g_Function = APP_shortestSide,
		.period = SHORTEST_SIDE_PERIOD
	},
	{
		.ptr_g_Function = APP_rotate,
		.period = ROTATE_PERIOD
	}};




	st_pinConfig st_g_pwmSignalPin = {PORTA_INDEX,DIO_PIN4,DIO_DIRECTION_OUTPUT,DIO_LOW,0};

	st_button st_g_startButton = {PORTD_INDEX,DIO_PIN1};
	st_button st_g_stopButton = {PORTD_INDEX,DIO_PIN2};

	st_leds	  st_g_longSideLed = {PORTB_INDEX,DIO_PIN0};
	st_leds	  st_g_shortSideLed = {PORTB_INDEX,DIO_PIN1};
	st_leds	  st_g_stopLed = {PORTB_INDEX,DIO_PIN2};
	st_leds	  st_g_rotateLed = {PORTB_INDEX,DIO_PIN3};
	

	
	interrupt_INTx_t st_g_startInterrupt;
	interrupt_INTx_t st_g_stopInterrupt;
	/*************************************************************************************/
	void APP_overflowRoutine()
	{
		static i8 i8_gs_overFlowCounter = 0;
		if (en_g_carStatus == SYSTEM_ON)
		{
			i8_gs_overFlowCounter++;
			if(st_g_systemSequence[u8_g_sequenceNumber].period == i8_gs_overFlowCounter)
			{
				i8_gs_overFlowCounter=-1;
				u8_g_sequenceNumber = (u8_g_sequenceNumber + 1) % SEQUENCE_MAX_NUMBER;
				u8_g_halfSecondStop = 1;
			}
			else
			{
				u8_g_halfSecondStop = 0;
			}
		}
		else if(en_g_carStatus == START_PRESSED)
		{
			i8_gs_overFlowCounter=-1;
			en_g_carStatus = SYSTEM_ON;
		}
	}
	/*************************************************************************************/
	void APP_pwmRoutine()
	{
		static u8 u8_a_flag = 0;
		if(u8_a_flag == 0){
			DIO_setPinStatus(&st_g_pwmSignalPin, DIO_HIGH);
			TIMER_preload(255 - u8_g_pwmDutyCycle,TIMER_TM0);
			u8_a_flag = 1;
			} else if(u8_a_flag == 1){
			DIO_setPinStatus(&st_g_pwmSignalPin, DIO_LOW);
			TIMER_preload(u8_g_pwmDutyCycle,TIMER_TM0);
			u8_a_flag = 0;
		}
		
	}
	/*************************************************************************************/
	//set pin A0..3 for motor directions
	//set pin D1 D2 for external interrupts input signal
	//set pin A4 for pwm signal output
	//set pin B0..3 for leds

	/************************************************/




	

	/**********************************************/
	en_appErrorStatus APP_init()
	{
		en_appErrorStatus en_appErrorStatus = APP_OK;
		st_g_startInterrupt.en_a_mode = INTERRUPT_FALLING_EDGE;
		st_g_startInterrupt.en_a_source = INTERRUPT_EXTERNAL_INT1;
		st_g_startInterrupt.EXT_InterruptHandler = APP_systemStart;
		
		en_appErrorStatus |= DIO_setPinDirection(&st_g_pwmSignalPin);
		
		en_appErrorStatus |= BUTTON_init(&st_g_startButton);
		en_appErrorStatus |= BUTTON_init(&st_g_stopButton);
		
		en_appErrorStatus |= LED_init(&st_g_longSideLed);
		en_appErrorStatus |= LED_init(&st_g_shortSideLed);
		en_appErrorStatus |= LED_init(&st_g_rotateLed);
		en_appErrorStatus |= LED_init(&st_g_stopLed);
		
		st_g_stopInterrupt.en_a_mode = INTERRUPT_FALLING_EDGE;
		st_g_stopInterrupt.en_a_source = INTERRUPT_EXTERNAL_INT0;
		st_g_stopInterrupt.EXT_InterruptHandler = APP_systemStop;

		en_appErrorStatus |= EXTI_interruptInit(&st_g_stopInterrupt);
		en_appErrorStatus |= EXTI_interruptInit(&st_g_stopInterrupt);
		
		en_appErrorStatus |= TIMER_init();
		en_appErrorStatus |= TIMER_setCallBack(TIMER0_OVF,APP_pwmRoutine);
		en_appErrorStatus |= TIMER_setCallBack(TIMER1_OVF,APP_overflowRoutine);
		en_appErrorStatus |= TIMER_preload(231,TIMER_TM0);
		
		en_appErrorStatus |= GIE_enableGeneralInterrupt();
		en_appErrorStatus |= MOTOR_DriverInitialize();
		
		return  en_appErrorStatus ;
	}
	void APP_systemStart()
	{
		/*write function*/
		TIMER_start(TIMER_TM0);
		TIMER_start(TIMER_TM1);
		en_g_carStatus = START_PRESSED;
		
	}
	en_appErrorStatus APP_longestSide()
	{
		
	}
	en_appErrorStatus APP_shortestSide();
	en_appErrorStatus APP_rotate();
	en_appErrorStatus APP_stop()
	{
		
	}
	void APP_systemStop()
	{
		/*write function*/
		en_g_carStatus = SYSTEM_OFF;
	}