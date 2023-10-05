/*
 * exti.c
 *
 * Created: 10/3/2023 2:09:10 PM
 *  Author: msharfeldin
 */ 

/***************************** INCLUDES SECTION ***********************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../gie/gie.h"
#include "exti.h"
// STATIC GLOBAL POINTERS TO FUNCTIONS TO HOLD THE CALLBACK POINTERS
static void (*v_gs_ptrfuncInt0)(void) = NULL ;
static void (*v_gs_ptrfuncInt1)(void) = NULL ;


/************************** FUNCTION DEFINETION ********************************/

/******************************************************************************/
/* Function: EXTI_interruptInit    @written by: Mahmoud Sharf-Eldin           */
/* I/P Parameters: interrupt_INTx_t										   */
/* Returns: en_extiErrorStatus				                                   */
/* Description: This Function initialize a given external interrupt           */
/******************************************************************************/
/* Options														           */
/*****************************************************************************/
/* mode     : FALLING_EDGE, RISING_EDGE, LOW_LEVEL, LOGICAL_CHANGE           */
/* source   : INT0, INT1, INT2        						               */
/*****************************************************************************/
en_extiErrorStatus EXTI_interruptInit(const interrupt_INTx_t *st_a_intObj)
{
	en_extiErrorStatus u8_a_retFunction = EXTI_OK;
	if (st_a_intObj == NULL) 
	{
		// to handle null pointer provide to function
		u8_a_retFunction = EXTI_NOK;
	}
	else
	{
		if (st_a_intObj->en_a_source == INTERRUPT_EXTERNAL_INT0)  // check if int0 to be initialized
		{
			// checking the mode at which int0 to be initialized
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
				// if unknown mode given to function 
				u8_a_retFunction = EXTI_WRONG_DATA;
			}
			//passing the callback function to the handler pointer
			v_gs_ptrfuncInt0 = st_a_intObj->EXT_InterruptHandler ; 
			// enable global interrupt and int0 
			EXT_INT0_InterruptEnable();
			GIE_enableGeneralInterrupt();
		}
		else if(st_a_intObj->en_a_source == INTERRUPT_EXTERNAL_INT1) // check if int1 to be initialized
		{
			// checking the mode at which int1 to be initialized
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
				// if unknown mode given to function 
				u8_a_retFunction = EXTI_WRONG_DATA;
			}
			//passing the callback function to the handler pointer
			v_gs_ptrfuncInt1 = st_a_intObj->EXT_InterruptHandler ;
			// enable global interrupt and int1
			EXT_INT1_InterruptEnable();
			GIE_enableGeneralInterrupt();
		}
		else
		{
			//if the user pass unknown source of external interrupt to the function
			u8_a_retFunction = EXTI_WRONG_DATA;
		}
	}
	return u8_a_retFunction;
	
}

  /******************************************************************************/
  /* Function: EXTI_interruptDeInit    @written by: Mahmoud Sharf-Eldin         */
  /* I/P Parameters: interrupt_INTx_t										    */
  /* Returns: en_extiErrorStatus				                                */
  /* Description: This Function de-initialize a given external interrupt        */
  /******************************************************************************/
  /* Options														            */
  /******************************************************************************/
  /* mode     : FALLING_EDGE, RISING_EDGE, LOW_LEVEL, LOGICAL_CHANGE            */
  /* source   : INT0, INT1, INT2        						                */
  /******************************************************************************/
  
en_extiErrorStatus EXTI_interruptDeInit(const interrupt_INTx_t *st_a_intObj)
{
	en_extiErrorStatus u8_a_retFunction = EXTI_OK;
	if (st_a_intObj == NULL)
	{
		// to handle null pointer provide to function
		u8_a_retFunction = EXTI_NOK;
	}
	else
	{
		if (st_a_intObj->en_a_source == INTERRUPT_EXTERNAL_INT0)
		{
			//handling the case of int0 chosen
			EXT_INT0_InterruptDisable();
		}
		else if(st_a_intObj->en_a_source == INTERRUPT_EXTERNAL_INT1)
		{
			//handling the case of int1 chosen
			EXT_INT1_InterruptDisable();
		}
		else
		{
			//if the user pass unknown source of external interrupt to the function
			u8_a_retFunction = EXTI_WRONG_DATA;
		}
	}
	return u8_a_retFunction;
}

//INTERRUPT SERVICE ROUTINE FOR INT0
void __vector_1 (void){
	// if the pointer to callback function is not null call it
	if(v_gs_ptrfuncInt0 != NULL) 
	{
		v_gs_ptrfuncInt0();
	}
	else
	{
		// do nothing
	}
}
//INTERRUPT SERVICE ROUTINE FOR INT0
void __vector_2 (void){
	// if the pointer to callback function is not null call it
	if(v_gs_ptrfuncInt1 != NULL) 
	{
		v_gs_ptrfuncInt1();
	}
	else
	{
		// do nothing
	}
}
