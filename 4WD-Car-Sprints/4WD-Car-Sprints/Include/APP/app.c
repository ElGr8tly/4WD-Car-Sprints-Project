/*
 * app.c
 *
 * Created: 10/3/2023 2:11:11 PM
 *  Author: melgreatly
 */ 
#include "../LIB/STD_TYPES.h"
#include "app.h"
#include "../MCAL/dio/dio.h"
#include "../MCAL/exti/exti.h"
#include "../MCAL/gie/gie.h"
#include "../MCAL/timer/timer.h"

#include "../HAL/button/button.h"
#include "../HAL/led/led.h"
#include "../HAL/motor_driver.h"

en_system_status en_g_carStatus = SYSTEM_OFF;

u8 u8_g_sequenceNumber = 0;
u8 u8_g_overflowCounter = 0;

u8 u8_g_halfSecondStop = 0;
car_mode st_g_systemSequence[SYSTEM_SEQ] = {{APP_longestSide,LONGEST_SIDE_PERIOD},
											{APP_rotate,ROTATE_PERIOD},
											{APP_shortestSide,SHORTEST_SIDE_PERIOD},{APP_rotate,ROTATE_PERIOD}};
interrupt_INTx_t st_g_start_button;
interrupt_INTx_t st_g_stop_button;

void APP_overflowRoutine()
{
	u8_g_overflowCounter++;
	if(st_g_systemSequence[u8_g_sequenceNumber].period == u8_g_overflowCounter)
	{
		u8_g_overflowCounter=0;
		st_g_systemSequence = (u8_g_sequenceNumber + 1) % SEQUENCE_MAX_NUMBER;
		u8_g_halfSecondStop = 1;
	}
	else
	{
		u8_g_halfSecondStop = 0;
	}
}
void APP_pwmRoutine();
	
void APP_init()
{
	st_g_start_button =
	{
		.en_a_mode = INTERRUPT_FALLING_EDGE,
		.en_a_source = INTERRUPT_EXTERNAL_INT1,
		.EXT_InterruptHandler = APP_systemStart
	};
	st_g_stop_button =
	{
		.en_a_mode = INTERRUPT_FALLING_EDGE,
		.en_a_source = INTERRUPT_EXTERNAL_INT0,
		.EXT_InterruptHandler = APP_stop
	};
	EXTI_interruptInit(&st_g_start_button);
	EXTI_interruptInit(&st_g_stop_button);
}
void APP_systemStart()
{
	/*write function*/
	en_g_carStatus = SYSTEM_ON;
}
void APP_longestSide();
void APP_shortestSide();
void APP_rotate();
void APP_stop()
{
	u8_g_overflowCounter = 0;
}
void APP_systemStop()
{
	/*write function*/
	en_g_carStatus = SYSTEM_OFF;
}