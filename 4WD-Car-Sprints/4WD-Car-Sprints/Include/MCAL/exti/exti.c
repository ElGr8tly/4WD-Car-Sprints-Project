/*
 * exti.c
 *
 * Created: 10/3/2023 2:09:10 PM
 *  Author: melgreatly
 */ 

/***************************** includes section *************************************************/
#include "../../LIB/STD_TYPES.h"
#include "exti.h"

static void (*v_gs_ptrfuncInt0)(void) = NULL ;
static void (*v_gs_ptrfuncInt1)(void) = NULL ;

en_extiErrorStatus EXTI_interruptInit(const interrupt_INTx_t *st_a_intObj)
{
	en_extiErrorStatus u8_a_retFunction = EXTI_OK;
	if (st_a_intObj == NULL)
	{
		u8_a_retFunction = EXTI_NOK;
	}
	else
	{
		if (st_a_intObj->en_a_source == INTERRUPT_EXTERNAL_INT0)
		{
			
			if (st_a_intObj->en_a_mode == INTERRUPT_LOW_LEVEL)
			{
				EXT_INT0_LowLevelSet();
			} 
			else if (st_a_intObj->en_a_mode == INTERRUPT_LOGICAL_CHANGE)
			{
				EXT_INT0_LogicalChangeSet();
			}
			else if (st_a_intObj->en_a_mode == INTERRUPT_RISING_EDGE)
			{
				EXT_INT0_RisingEdgeSet();
			}
			else if (st_a_intObj->en_a_mode == INTERRUPT_FALLING_EDGE)
			{
				EXT_INT0_FallingEdgeSet();
			}
			else
			{
				u8_a_retFunction = EXTI_WRONG_DATA;
			}
			v_gs_ptrfuncInt0 = st_a_intObj->EXT_InterruptHandler ; 
			EXT_INT0_InterruptEnable();
		}
		else if(st_a_intObj->en_a_source == INTERRUPT_EXTERNAL_INT1)
		{
			
			if (st_a_intObj->en_a_mode == INTERRUPT_LOW_LEVEL)
			{
				EXT_INT1_LowLevelSet();
			}
			else if (st_a_intObj->en_a_mode == INTERRUPT_LOGICAL_CHANGE)
			{
				EXT_INT1_LogicalChangeSet();
			}
			else if (st_a_intObj->en_a_mode == INTERRUPT_RISING_EDGE)
			{
				EXT_INT1_RisingEdgeSet();
			}
			else if (st_a_intObj->en_a_mode == INTERRUPT_FALLING_EDGE)
			{
				EXT_INT1_FallingEdgeSet();
			}
			else
			{
				u8_a_retFunction = EXTI_WRONG_DATA;
			}
			v_gs_ptrfuncInt1 = st_a_intObj->EXT_InterruptHandler ;
			EXT_INT1_InterruptEnable();
		}
		else
		{
			u8_a_retFunction = EXTI_WRONG_DATA;
		}
	}
	return u8_a_retFunction;
	
}


en_extiErrorStatus EXTI_interruptDeInit(const interrupt_INTx_t *st_a_intObj)
{
	en_extiErrorStatus u8_a_retFunction = EXTI_OK;
	if (st_a_intObj == NULL)
	{
		u8_a_retFunction = EXTI_NOK;
	}
	else
	{
		if (st_a_intObj->en_a_source == INTERRUPT_EXTERNAL_INT0)
		{
			
			EXT_INT0_InterruptDisable();
		}
		else if(st_a_intObj->en_a_source == INTERRUPT_EXTERNAL_INT1)
		{
			
			EXT_INT1_InterruptDisable();
		}
		else
		{
			u8_a_retFunction = EXTI_WRONG_DATA;
		}
	}
	return u8_a_retFunction;
}


void __vector_1 (void){
	if(v_gs_ptrfuncInt0 != NULL) 
	{
		v_gs_ptrfuncInt0();
	}
	else
	{
		// do nothing
	}
}
void __vector_2 (void){
	if(v_gs_ptrfuncInt1 != NULL) 
	{
		v_gs_ptrfuncInt1();
	}
	else
	{
		// do nothing
	}
}
