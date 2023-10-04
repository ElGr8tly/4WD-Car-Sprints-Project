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
st_carMode st_g_systemSequence[SYSTEM_SEQ] = {
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

												
interrupt_INTx_t st_g_start_button;
interrupt_INTx_t st_g_stop_button;
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
			st_g_systemSequence = (u8_g_sequenceNumber + 1) % SEQUENCE_MAX_NUMBER;
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
en_appErrorStatus APP_pwmRoutine();
/*************************************************************************************/	
en_appErrorStatus APP_init()
{
	en_appErrorStatus en_appErrorStatus = APP_OK;
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
		.EXT_InterruptHandler = APP_systemStop
	};
	en_appErrorStatus |= EXTI_interruptInit(&st_g_start_button);
	en_appErrorStatus |= EXTI_interruptInit(&st_g_stop_button);
	
	return = en_appErrorStatus ;
}
void APP_systemStart()
{
	/*write function*/
	en_g_carStatus = START_PRESSED;
	
}
en_appErrorStatus APP_longestSide();
en_appErrorStatus APP_shortestSide();
en_appErrorStatus APP_rotate();
en_appErrorStatus APP_stop()
{
	
}
en_appErrorStatus APP_systemStop()
{
	/*write function*/
	en_g_carStatus = SYSTEM_OFF;
}