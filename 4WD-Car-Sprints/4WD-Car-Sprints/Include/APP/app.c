/*
* app.c
*
* Created: 10/3/2023 2:11:11 PM
*  Author:
*/
/********************* INCLUDES SECTION ***********************/
#include "app.h"

/******************** GLOBAL VARIABLES DEFINETIONS *******************/

en_systemStatus en_g_carStatus = SYSTEM_OFF;

u8 u8_g_sequenceNumber = 0;

u8 u8_g_halfSecondStop = 0;

u8 u8_g_pwmDutyCycle = 128;

u16 u16_g_timerLastValue = 0;
st_leds *st_g_currentLed ;
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
	}
};

st_pinConfig	st_g_pwmSignalPin	= {PORTA_INDEX,DIO_PIN4,DIO_DIRECTION_OUTPUT,DIO_HIGH,DIO_UNLOCK};
st_button		st_g_startButton	= {PORTD_INDEX,DIO_PIN1};
st_button		st_g_stopButton		= {PORTD_INDEX,DIO_PIN2};
	
st_leds			st_g_longSideLed	= {PORTB_INDEX,DIO_PIN0};
st_leds			st_g_shortSideLed	= {PORTB_INDEX,DIO_PIN1};
st_leds			st_g_stopLed		= {PORTB_INDEX,DIO_PIN2};
st_leds			st_g_rotateLed		= {PORTB_INDEX,DIO_PIN3};
	
interrupt_INTx_t st_g_startInterrupt =
{
	.en_a_mode				= INTERRUPT_FALLING_EDGE,
	.en_a_source			= INTERRUPT_EXTERNAL_INT1,
	.EXT_InterruptHandler	= APP_systemStart,	
};
interrupt_INTx_t st_g_stopInterrupt =
{
	.en_a_mode = INTERRUPT_FALLING_EDGE,
	.en_a_source = INTERRUPT_EXTERNAL_INT0,
	.EXT_InterruptHandler = APP_systemStop,	
};

/********************** FUNCTIONS DEFINITIONS ***************************************/

void APP_overflowRoutine()
{
	static i8 i8_gs_overFlowCounter = 0;
	TIMER_preload(3035,TIMER_TM1); 
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
/*timer0 ovf routine for generating pwm signals*/
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


/*initialize application function*/
en_appErrorStatus APP_init()
{
	en_appErrorStatus en_a_appErrorStatus = APP_OK;	
	en_a_appErrorStatus |= DIO_setPinDirection(&st_g_pwmSignalPin);
		
	//en_a_appErrorStatus |= BUTTON_init(&st_g_startButton);
	//en_a_appErrorStatus |= BUTTON_init(&st_g_stopButton);
	//en_a_appErrorStatus |= BUTTON_connectIPU(&st_g_startButton);
	//en_a_appErrorStatus |= BUTTON_connectIPU(&st_g_stopButton);
		
	DIO_DDRD = 0;
	DIO_PORTD = 0xff;
		
	en_a_appErrorStatus |= LED_init(&st_g_longSideLed);
	en_a_appErrorStatus |= LED_init(&st_g_shortSideLed);
	en_a_appErrorStatus |= LED_init(&st_g_rotateLed);
	en_a_appErrorStatus |= LED_init(&st_g_stopLed);


	en_a_appErrorStatus |= EXTI_interruptInit(&st_g_startInterrupt);
	en_a_appErrorStatus |= EXTI_interruptInit(&st_g_stopInterrupt);
		
	en_a_appErrorStatus |= TIMER_init();
	en_a_appErrorStatus |= TIMER_setCallBack(TIMER0_OVF,APP_pwmRoutine);
	en_a_appErrorStatus |= TIMER_setCallBack(TIMER1_OVF,APP_overflowRoutine);
	en_a_appErrorStatus |= TIMER_preload(231,TIMER_TM0);
		
	en_a_appErrorStatus |= GIE_enableGeneralInterrupt();
	en_a_appErrorStatus |= MOTOR_driverInitialize();
	
	
		
	return  en_a_appErrorStatus ;
}
/******************************************************************************/
/*start button external interrupt Rooutine*/
void APP_systemStart()
{
	st_leds led = {PORTC_INDEX,DIO_PIN0};
	LED_init(&led);
	
	LED_on(&led);
	if(en_g_carStatus == SYSTEM_OFF)
	{
		TIMER_start(TIMER_TM0);
		TIMER_start(TIMER_TM1);
		en_g_carStatus = START_PRESSED;
		TIMER_preload(TIMER_TM1,u16_g_timerLastValue);
	}
	else
	{
	}
		
}
/************************************************************************************/

/***********************************************************************************/
/*longest side of the rectangle*/
en_appErrorStatus APP_longestSide()
{
	u8_g_pwmDutyCycle = 128;
	en_appErrorStatus en_a_appErrorStatus = APP_OK;
	
	en_a_appErrorStatus |= LED_off(st_g_currentLed);	
	st_g_currentLed    = &st_g_longSideLed;
	en_a_appErrorStatus |= LED_on(st_g_currentLed);
	
	en_a_appErrorStatus |= MOTOR_leftMotorForwardDirection();
	en_a_appErrorStatus |= MOTOR_rightMotorForwardDirection();
	return en_a_appErrorStatus ;
}
/*************************************************************************************/
/*shortest side of the rectangle*/
en_appErrorStatus APP_shortestSide()
{
	u8_g_pwmDutyCycle = 77;
	en_appErrorStatus en_a_appErrorStatus = APP_OK;
	
	en_a_appErrorStatus |= LED_off(st_g_currentLed);
	st_g_currentLed    = &st_g_shortSideLed;
	en_a_appErrorStatus |= LED_on(st_g_currentLed);
	
	en_a_appErrorStatus |= MOTOR_leftMotorForwardDirection();
	en_a_appErrorStatus |= MOTOR_rightMotorForwardDirection();
	return en_a_appErrorStatus ;
}
/*****************************************************************/
/*rotate the robot*/
en_appErrorStatus APP_rotate()
{
	en_appErrorStatus en_a_appErrorStatus = APP_OK;
	
	en_a_appErrorStatus |= LED_off(st_g_currentLed);
	st_g_currentLed    = &st_g_rotateLed;
	en_a_appErrorStatus |= LED_on(st_g_currentLed);
	
	en_a_appErrorStatus |= MOTOR_leftMotorBackwardDirection();
	en_a_appErrorStatus |= MOTOR_rightMotorForwardDirection();
	return en_a_appErrorStatus;
}
/******************************************************************/
/*stop car for half second*/
en_appErrorStatus APP_temporaryStop()
{
	en_appErrorStatus en_a_appErrorStatus = APP_OK;
	
	en_a_appErrorStatus |= LED_off(st_g_currentLed);
	st_g_currentLed    = &st_g_stopLed;
	en_a_appErrorStatus |= LED_on(st_g_currentLed);
	
	en_a_appErrorStatus |= MOTOR_stopMotorDirection();
	return en_a_appErrorStatus;	
}
/********************************************************************/
/*start button external interrupt Routine*/
void APP_systemStop()
{
	/*st_leds led = {PORTC_INDEX,DIO_PIN0};
	LED_init(&led);
	
	LED_on(&led);*/
	en_appErrorStatus en_a_appErrorStatus = APP_OK;
	TIMER_read(TIMER_TM1,&u16_g_timerLastValue);
	TIMER_stop(TIMER_TM0);
	TIMER_stop(TIMER_TM1);
	MOTOR_stopMotorDirection();
	en_g_carStatus = SYSTEM_OFF;
	
	en_a_appErrorStatus |= LED_off(st_g_currentLed);
	st_g_currentLed    = &st_g_stopLed;
	en_a_appErrorStatus |= LED_on(st_g_currentLed);
}
/***********************************************************************/