/*
 * gie.c
 *
 * Created: 10/3/2023 2:09:36 PM
 *  Author: msharfeldin
 */ 
/***************************** INCLUDE SECTION *************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "gie.h"


/************************** FUNCTIONS DEFINETIONS ************************/

/******************************************************************************/
/* Function: GIE_enableGeneralInterrupt    @written by: Mahmoud Sharf-Eldin   */
/* Returns: en_gieErrorStatus				                                  */
/* Description: This Function enable global interrupts                        */
/******************************************************************************/

en_gieErrorStatus GIE_enableGeneralInterrupt(void)
{
	en_gieErrorStatus u8_a_retFunction = GIE_OK;
	SET_BIT(SREG, GLOBAL_INTERRUPT_ENABLE_BIT);
	return u8_a_retFunction;
	
}

/******************************************************************************/
/* Function: GIE_disableGeneralInterrupt    @written by: Mahmoud Sharf-Eldin  */
/* Returns: en_gieErrorStatus				                                  */
/* Description: This Function disable global interrupts                       */
/******************************************************************************/

en_gieErrorStatus GIE_disableGeneralInterrupt(void)
{
	en_gieErrorStatus u8_a_retFunction = GIE_OK;
	CLEAR_BIT(SREG, GLOBAL_INTERRUPT_ENABLE_BIT);
	return u8_a_retFunction;
	
}
