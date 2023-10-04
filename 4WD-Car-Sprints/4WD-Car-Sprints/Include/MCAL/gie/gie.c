/*
 * gie.c
 *
 * Created: 10/3/2023 2:09:36 PM
 *  Author: melgreatly
 */ 
/***************************** includes section *************************************************/
#include "../4WD-Car-Sprints/Include/LIB/STD_TYPES.h"
#include "gie.h"

en_gieErrorStatus GIE_enableGeneralInterrupt(void)
{
	en_gieErrorStatus u8_a_retFunction = GIE_OK;
	SET_BIT(SREG, GLOBAL_INTERRUPT_ENABLE_BIT);
	return u8_a_retFunction;
	
}

en_gieErrorStatus GIE_disableGeneralInterrupt(void)
{
	en_gieErrorStatus u8_a_retFunction = GIE_OK;
	CLEAR_BIT(SREG, GLOBAL_INTERRUPT_ENABLE_BIT);
	return u8_a_retFunction;
	
}
