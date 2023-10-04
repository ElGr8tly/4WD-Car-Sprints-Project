/*
 * gie.c
 *
 * Created: 10/3/2023 2:09:36 PM
 *  Author: melgreatly
 */ 
/***************************** includes section *************************************************/
#include "gie.h"

u8_returnType GIE_enableGeneralInterrupt(void)
{
	u8_returnType u8_a_retFunction = E_OK;
	SET_BIT(SREG, GLOBAL_INTERRUPT_ENABLE_BIT);
	return u8_a_retFunction;
	
}

u8_returnType GIE_disableGeneralInterrupt(void)
{
	u8_returnType u8_a_retFunction = E_OK;
	CLEAR_BIT(SREG, GLOBAL_INTERRUPT_ENABLE_BIT);
	return u8_a_retFunction;
	
}
