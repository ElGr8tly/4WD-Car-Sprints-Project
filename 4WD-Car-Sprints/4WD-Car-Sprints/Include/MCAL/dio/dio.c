/*
 * dio.c
 *  Created: 10/3/2023 2:08:45 PM
 *  Author: Elgreatly and Mansour
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "dio.h"

 /* Section: Function Definitions */

 /******************************************************************************/
 /* Function: DIO_pinInit    @written by: Mohamed El-Greatly                   */
 /* I/P Parameters: st_pinConfig,								               */
 /* Returns: en_dioErrorStatus				                                   */
 /* Description: This Function initialize a given pin				           */
 /******************************************************************************/
 /* Options														               */
 /******************************************************************************/
 /* port     : port0..3												           */
 /* pin      : pin0 ..7       									               */
 /* direction: 0 or 1		        		                      	           */
 /* logic    : 0 or 1 if direction = 0                                         */
 /******************************************************************************/
en_dioErrorStatus DIO_pinInitialize(const st_pinConfig* st_a_pinConfig)
{
	en_dioErrorStatus en_a_retFunction = DIO_OK;
	if (st_a_pinConfig != NULL)
	{
		if (st_a_pinConfig->u8_g_reserved == DIO_UNLOCK)
		{
			en_a_retFunction &= DIO_setPinDirection(st_a_pinConfig);
			en_a_retFunction &= DIO_setPinStatus((st_pinConfig*) st_a_pinConfig, st_a_pinConfig->u8_g_logic);
		}
		else  /* Wrong data casted to pinConfig struct */
		{
			en_a_retFunction = DIO_WRONG_INPUT;
		}

	}
	else
	{
		en_a_retFunction = DIO_WRONG_INPUT;
	}

	return en_a_retFunction;
}

/****************************************************************************************************************
 * @written by: Mohamed Mansour.
 * @brief Set the direction (input or output) of a specific GPIO pin.
 *
 * This function is responsible for configuring the direction (input or output) of a specified
 * GPIO pin on a particular port.
 *
 * @param st_a_pinConfig Pointer to a structure containing pin configuration information.
 * @return en_dioErrorStatus representing the success or failure of the operation.
 *         - DIO_OK: Operation successful.
 *         - DIO_WRONG_INPUT: Invalid input parameters or reserved value encountered in the pin configuration.
 ****************************************************************************************************************/
en_dioErrorStatus DIO_setPinDirection(const st_pinConfig* st_a_pinConfig)
{
	en_dioErrorStatus en_a_retFunction = DIO_OK;
	// Check if the input pointer is not NULL
	if (st_a_pinConfig != NULL)
	{
		 // Check if the pin is not reserved (DIO_UNLOCK)
		if (st_a_pinConfig->u8_g_reserved == DIO_UNLOCK)
		{
			// Determine the port and set the pin direction accordingly
			switch (st_a_pinConfig->u8_g_port)
			{
			case PORTA_INDEX:
				if (st_a_pinConfig->u8_g_direction == DIO_DIRECTION_INPUT) 
				{
					CLR_BIT(DIO_DDRA, st_a_pinConfig->u8_g_pin);	// Set the pin as an input
				}
				else
				{
					SET_BIT(DIO_DDRA, st_a_pinConfig->u8_g_pin);	// Set the pin as an output
				}
				break;
			case PORTB_INDEX:

				if (st_a_pinConfig->u8_g_direction == DIO_DIRECTION_INPUT)
				{
					CLR_BIT(DIO_DDRB, st_a_pinConfig->u8_g_pin);	// Set the pin as an input
				}
				else
				{
					SET_BIT(DIO_DDRB, st_a_pinConfig->u8_g_pin);	// Set the pin as an output
				}
				break;
			case PORTC_INDEX:
				if (st_a_pinConfig->u8_g_direction == DIO_DIRECTION_INPUT)
				{
					CLR_BIT(DIO_DDRC, st_a_pinConfig->u8_g_pin);	// Set the pin as an input
				}
				else
				{
					SET_BIT(DIO_DDRC, st_a_pinConfig->u8_g_pin);	// Set the pin as an output
				}
				break;
			case PORTD_INDEX:
				if (st_a_pinConfig->u8_g_direction == DIO_DIRECTION_INPUT)
				{
					CLR_BIT(DIO_DDRD, st_a_pinConfig->u8_g_pin);	// Set the pin as an input
				}
				else
				{
					SET_BIT(DIO_DDRD, st_a_pinConfig->u8_g_pin);	// Set the pin as an output
				}
				break;
			default:
				 // Handle the case of an invalid port index
				 en_a_retFunction = DIO_WRONG_INPUT;
				 break;

			}
		}
		else  /* Wrong data casted to pinConfig struct */
		{
			en_a_retFunction = DIO_WRONG_INPUT;
		}

	}
	else
	{
		en_a_retFunction = DIO_WRONG_INPUT;
	}
	 // Return the status of the operation
	return en_a_retFunction;
}
/***********************************************************************************************************
 * @written by: Mohamed Mansour.
 * @brief Get the direction (input or output) of a specific GPIO pin.
 *
 * This function retrieves the current direction (input or output) of a specified
 * GPIO pin on a particular port and stores the result in the provided 'en_a_directionStatus' variable.
 *
 * @param st_a_pinConfig Pointer to a structure containing pin configuration information.
 * @param en_a_directionStatus Pointer to a variable where the pin's direction will be stored.
 * @return en_dioErrorStatus representing the success or failure of the operation.
 *         - DIO_OK: Operation successful.
 *         - DIO_WRONG_INPUT: Invalid input parameters or reserved value encountered in the pin configuration.
 ****************************************************************************************************************/
en_dioErrorStatus DIO_getPinDirection(st_pinConfig* st_a_pinConfig, en_pinDirection* en_a_directionStatus)
{
	en_dioErrorStatus en_a_retFunction = DIO_OK;
	 // Check if the input pointer is not NULL
	if (st_a_pinConfig != NULL)
	{
		 // Check if the pin is not reserved (DIO_UNLOCK)
		if (st_a_pinConfig->u8_g_reserved == DIO_UNLOCK)
		{
			  // Determine the port and read the pin direction, then store it in 'en_a_directionStatus'
			switch(st_a_pinConfig->u8_g_port)
			{
				case PORTA_INDEX:
				*en_a_directionStatus = GET_BIT(DIO_DDRA,st_a_pinConfig->u8_g_pin);
				break;
				case PORTB_INDEX:
				*en_a_directionStatus = GET_BIT(DIO_DDRB,st_a_pinConfig->u8_g_pin);
				break;
				case PORTC_INDEX:
				*en_a_directionStatus = GET_BIT(DIO_DDRC,st_a_pinConfig->u8_g_pin);
				break;
				case PORTD_INDEX:
				*en_a_directionStatus = GET_BIT(DIO_DDRD,st_a_pinConfig->u8_g_pin);
				break;
			default:
				// Handle the case of an invalid port index
				en_a_retFunction = DIO_WRONG_INPUT;
				break;
			}
		    // Update the 'u8_g_direction' field in the 'st_a_pinConfig' structure
			st_a_pinConfig->u8_g_direction = *en_a_directionStatus;
		}
		else  /* Wrong data casted to pinConfig struct */
		{
			en_a_retFunction = DIO_WRONG_INPUT;
		}

	}
	else
	{
		en_a_retFunction = DIO_WRONG_INPUT;
	}
	// Return the status of the operation
	return en_a_retFunction;
}
/**
 * @written by: Mohamed Mansour.
 * @brief Set the status (high or low) of a specific GPIO pin.
 * This function is responsible for configuring the logic level (high or low) of a specified GPIO pin
 * on a particular port based on the provided 'en_a_bitLogic' parameter.
 *
 * @param st_a_pinConfig Pointer to a structure containing pin configuration information.
 * @param en_a_bitLogic The desired logic level for the pin (DIO_HIGH or DIO_LOW).
 * @return en_dioErrorStatus representing the success or failure of the operation.
 *         - DIO_OK: Operation successful.
 *         - DIO_NOK: Operation failed, possibly due to the pin being configured as an input.
 *         - DIO_WRONG_INPUT: Invalid input parameters or reserved value encountered in the pin configuration.
 */
en_dioErrorStatus DIO_setPinStatus(st_pinConfig* st_a_pinConfig, en_bitLogic en_a_bitLogic)
{
	en_dioErrorStatus en_a_retFunction = DIO_OK;
	// Check if the input pointer is not NULL
	if (st_a_pinConfig != NULL)
	{
		// Check if the pin is not reserved (DIO_UNLOCK)
		if (st_a_pinConfig->u8_g_reserved == DIO_UNLOCK)
		{
			// Ensure 'en_a_bitLogic' is either DIO_HIGH or DIO_LOW
			en_a_bitLogic &= DIO_HIGH;
			 // Determine the port and set the pin status (high or low) based on the direction
			switch (st_a_pinConfig->u8_g_port)
			{
			case PORTA_INDEX:
				if (GET_BIT(DIO_DDRA, st_a_pinConfig->u8_g_pin) == DIO_DIRECTION_INPUT)
				{
					en_a_retFunction = DIO_NOK;			// Cannot set the status of an input pin
				}
				else
				{
					// Set or clear the pin based on 'en_a_bitLogic' and update 'u8_g_logic' in 'st_a_pinConfig'
					if (en_a_bitLogic == DIO_LOW)
					{
						CLR_BIT(DIO_PORTA, st_a_pinConfig->u8_g_pin);
						st_a_pinConfig->u8_g_logic = DIO_LOW;
					}
					else
					{
						SET_BIT(DIO_PORTA, st_a_pinConfig->u8_g_pin);
						st_a_pinConfig->u8_g_logic = DIO_HIGH;
					}
				}
				break;

			case PORTB_INDEX:
				if (GET_BIT(DIO_DDRB, st_a_pinConfig->u8_g_pin) == DIO_DIRECTION_INPUT)
				{
					en_a_retFunction = DIO_NOK;
				}
				else
				{
					if (en_a_bitLogic == DIO_LOW)
					{
						CLR_BIT(DIO_PORTB, st_a_pinConfig->u8_g_pin);
						st_a_pinConfig->u8_g_logic = DIO_LOW;
					}
					else
					{
						SET_BIT(DIO_PORTB, st_a_pinConfig->u8_g_pin);
						st_a_pinConfig->u8_g_logic = DIO_HIGH;
					}
				}
				break;

			case PORTC_INDEX:
				if (GET_BIT(DIO_DDRC, st_a_pinConfig->u8_g_pin) == DIO_DIRECTION_INPUT)
				{
					en_a_retFunction = DIO_NOK;
				}
				else
				{
					if (en_a_bitLogic == DIO_LOW)
					{
						CLR_BIT(DIO_PORTC, st_a_pinConfig->u8_g_pin);
						st_a_pinConfig->u8_g_logic = DIO_LOW;
					}
					else
					{
						SET_BIT(DIO_PORTC, st_a_pinConfig->u8_g_pin);
						st_a_pinConfig->u8_g_logic = DIO_HIGH;
					}
				}
				break;

			case PORTD_INDEX:
				if (GET_BIT(DIO_DDRD, st_a_pinConfig->u8_g_pin) == DIO_DIRECTION_INPUT)
				{
					en_a_retFunction = DIO_NOK;
				}
				else
				{
					if (en_a_bitLogic == DIO_LOW)
					{
						CLR_BIT(DIO_PORTD, st_a_pinConfig->u8_g_pin);
						st_a_pinConfig->u8_g_logic = DIO_LOW;
					}
					else
					{
						SET_BIT(DIO_PORTD, st_a_pinConfig->u8_g_pin);
						st_a_pinConfig->u8_g_logic = DIO_HIGH;
					}
				}
				break;
			}
		}
		else  /* Wrong data casted to pinConfig struct */
		{
			en_a_retFunction = DIO_WRONG_INPUT;
		}
	}
	else
	{
		en_a_retFunction = DIO_WRONG_INPUT;
	}

	return en_a_retFunction;

}
/**
 * @written by: Mohamed Mansour.
 * @brief Get the logic level (high or low) of a specific GPIO pin.
 *
 * This function retrieves the current logic level (high or low) of a specified GPIO pin on a
 * particular port and stores the result in the provided 'en_a_bitLogic' variable.
 *
 * @param st_a_pinConfig Pointer to a structure containing pin configuration information.
 * @param en_a_bitLogic Pointer to a variable where the pin's logic level will be stored (DIO_HIGH or DIO_LOW).
 * @return en_dioErrorStatus representing the success or failure of the operation.
 *         - DIO_OK: Operation successful.
 *         - DIO_WRONG_INPUT: Invalid input parameters or reserved value encountered in the pin configuration.
 */
en_dioErrorStatus DIO_getPinStatus(st_pinConfig* st_a_pinConfig, en_bitLogic* en_a_bitLogic) 
{
	en_dioErrorStatus en_a_retFunction = DIO_OK;
	// Check if the input pointer is not NULL
	if (st_a_pinConfig != NULL)
	{
		// Check if the pin is not reserved (DIO_UNLOCK)
		if (st_a_pinConfig->u8_g_reserved == DIO_UNLOCK)
		{
			// Determine the port and read the pin status (high or low) and store it in 'en_a_bitLogic'
			switch(st_a_pinConfig->u8_g_port)
			{
				case PORTA_INDEX:
				*en_a_bitLogic = GET_BIT(DIO_PORTA,st_a_pinConfig->u8_g_pin);
				break;
				case PORTB_INDEX:
				*en_a_bitLogic = GET_BIT(DIO_PORTB,st_a_pinConfig->u8_g_pin);
				break;
				case PORTC_INDEX:
				*en_a_bitLogic = GET_BIT(DIO_PORTC,st_a_pinConfig->u8_g_pin);
				break;
				case PORTD_INDEX:
				*en_a_bitLogic = GET_BIT(DIO_PORTD,st_a_pinConfig->u8_g_pin);
				break;
			}
			// Update the 'u8_g_logic' field in the 'st_a_pinConfig' structure
			st_a_pinConfig->u8_g_logic = *en_a_bitLogic;
        }
		else  /* Wrong data casted to pinConfig struct */
		{
			en_a_retFunction = DIO_WRONG_INPUT;
		}
	}
	else
	{
		en_a_retFunction = DIO_WRONG_INPUT;
	}

	return en_a_retFunction;

}
/******************************************************************************/
/* Function: DIO_togglePinStatus    @written by: Mohamed El-Greatly           */
/* I/P Parameters: st_pinConfig 								              */
/* Returns: en_dioErrorStatus				                                  */
/* Description: This Function Toggle Pin Logic                                */
/******************************************************************************/
/* Options														              */
/******************************************************************************/
/* port     : port0..3												          */
/* pin      : pin0 ..7       									              */
/* logic    : 0 or 1 if direction = 0                                         */
/******************************************************************************/
en_dioErrorStatus DIO_togglePinStatus(st_pinConfig* st_a_pinConfig)
{
	en_dioErrorStatus en_a_retFunction = DIO_OK;
	en_bitLogic en_a_bitLogic = DIO_HIGH;
	if (st_a_pinConfig != NULL)
	{
		if (st_a_pinConfig->u8_g_reserved == DIO_UNLOCK)
		{

			en_a_retFunction = DIO_getPinStatus(st_a_pinConfig, &en_a_bitLogic);
			if (en_a_retFunction == DIO_OK)
			{
				en_a_bitLogic ^= LOGIC_HIGH;
				en_a_retFunction = DIO_setPinStatus(st_a_pinConfig, en_a_bitLogic);
			}
		}
		else  /* Wrong data casted to pinConfig struct */
		{
			en_a_retFunction = DIO_WRONG_INPUT;
		}

	}
	else
	{
		en_a_retFunction = DIO_WRONG_INPUT;
	}

	return en_a_retFunction;
}
/******************************************************************************/
/* Function: DIO_setPinPullupResistor    @written by: Mohamed El-Greatly      */
/* I/P Parameters: st_pinConfig 								              */
/* Returns: en_dioErrorStatus				                                  */
/* Description: This Function Set Input Pin Hardware PullupResistor           */
/******************************************************************************/
/* Options														              */
/******************************************************************************/
/* port     : port0..3												          */
/* pin      : pin0 ..7       									              */
/******************************************************************************/
en_dioErrorStatus DIO_setPinPullupResistor(const st_pinConfig* st_a_pinConfig)
{
	en_dioErrorStatus en_a_retFunction = DIO_OK;
	if (st_a_pinConfig != NULL)
	{
		if (st_a_pinConfig->u8_g_reserved == DIO_UNLOCK)
		{
			switch (st_a_pinConfig->u8_g_port)
			{
			case PORTA_INDEX:
				if (GET_BIT(DIO_DDRA, st_a_pinConfig->u8_g_pin) == DIO_DIRECTION_INPUT)
				{
					SET_BIT(DIO_PORTA, st_a_pinConfig->u8_g_pin);
				}
				else
				{
					en_a_retFunction = DIO_NOK;
				}
				break;

			case PORTB_INDEX:
				if (GET_BIT(DIO_DDRB, st_a_pinConfig->u8_g_pin) == DIO_DIRECTION_INPUT)
				{
					SET_BIT(DIO_PORTB, st_a_pinConfig->u8_g_pin);
				}
				else
				{
					en_a_retFunction = DIO_NOK;
				}
				break;

			case PORTC_INDEX:
				if (GET_BIT(DIO_DDRC, st_a_pinConfig->u8_g_pin) == DIO_DIRECTION_INPUT)
				{
					SET_BIT(DIO_PORTC, st_a_pinConfig->u8_g_pin);
				}
				else
				{
					en_a_retFunction = DIO_NOK;
				}
				break;

			case PORTD_INDEX:
				if (GET_BIT(DIO_DDRD, st_a_pinConfig->u8_g_pin) == DIO_DIRECTION_INPUT)
				{
					SET_BIT(DIO_PORTD, st_a_pinConfig->u8_g_pin);
				}
				else
				{
					en_a_retFunction = DIO_NOK;
				}
				break;
			}
		}
		else  /* Wrong data casted to pinConfig struct */
		{
			en_a_retFunction = DIO_WRONG_INPUT;
		}

	}
	else
	{
		en_a_retFunction = DIO_WRONG_INPUT;
	}

	return en_a_retFunction;
}
/******************************************************************************/
/* Function: DIO_disablePinPullupResistor    @written by: Mohamed El-Greatly  */
/* I/P Parameters: st_pinConfig 								              */
/* Returns: en_dioErrorStatus				                                  */
/* Description: This Function Disable Input Pin Hardware PullupResistor       */
/******************************************************************************/
/* Options														              */
/******************************************************************************/
/* port     : port0..3												          */
/* pin      : pin0 ..7       									              */
/******************************************************************************/
en_dioErrorStatus DIO_disablePinPullupResistor(const st_pinConfig* st_a_pinConfig)
{
	en_dioErrorStatus en_a_retFunction = DIO_OK;
	if (st_a_pinConfig != NULL)
	{
		if (st_a_pinConfig->u8_g_reserved == DIO_UNLOCK)
		{
			switch (st_a_pinConfig->u8_g_port)
			{
			case PORTA_INDEX:
				if (GET_BIT(DIO_DDRA, st_a_pinConfig->u8_g_pin) == DIO_DIRECTION_INPUT)
				{
					CLR_BIT(DIO_PORTA, st_a_pinConfig->u8_g_pin);
				}
				else
				{
					en_a_retFunction = DIO_NOK;
				}
				break;

			case PORTB_INDEX:
				if (GET_BIT(DIO_DDRB, st_a_pinConfig->u8_g_pin) == DIO_DIRECTION_INPUT)
				{
					CLR_BIT(DIO_PORTB, st_a_pinConfig->u8_g_pin);
				}
				else
				{
					en_a_retFunction = DIO_NOK;
				}
				break;

			case PORTC_INDEX:
				if (GET_BIT(DIO_DDRC, st_a_pinConfig->u8_g_pin) == DIO_DIRECTION_INPUT)
				{
					CLR_BIT(DIO_PORTC, st_a_pinConfig->u8_g_pin);
				}
				else
				{
					en_a_retFunction = DIO_NOK;
				}
				break;

			case PORTD_INDEX:
				if (GET_BIT(DIO_DDRD, st_a_pinConfig->u8_g_pin) == DIO_DIRECTION_INPUT)
				{
					CLR_BIT(DIO_PORTD, st_a_pinConfig->u8_g_pin);
				}
				else
				{
					en_a_retFunction = DIO_NOK;
				}
				break;
			}
		}
		else  /* Wrong data casted to pinConfig struct */
		{
			en_a_retFunction = DIO_WRONG_INPUT;
		}

	}
	else
	{
		en_a_retFunction = DIO_WRONG_INPUT;
	}

	return en_a_retFunction;

}
/******************************************************************************/
en_dioErrorStatus DIO_lockPin(st_pinConfig* st_a_pinConfig)
{
	en_dioErrorStatus en_a_retFunction = DIO_OK;
	if (st_a_pinConfig != NULL)
	{
		if (st_a_pinConfig->u8_g_reserved == DIO_UNLOCK)
		{
			st_a_pinConfig->u8_g_reserved = DIO_LOCK;
		}
		else
		{
			en_a_retFunction = DIO_NOK;
		}

	}
	else
	{
		en_a_retFunction = DIO_WRONG_INPUT;
	}
	return en_a_retFunction;
}
en_dioErrorStatus DIO_unlockPin(st_pinConfig* st_a_pinConfig)
{
	en_dioErrorStatus en_a_retFunction = DIO_OK;
	if (st_a_pinConfig != NULL)
	{
		if (st_a_pinConfig->u8_g_reserved == DIO_LOCK)
		{
			st_a_pinConfig->u8_g_reserved = DIO_UNLOCK;
		}
		else
		{
			en_a_retFunction = DIO_NOK;
		}

	}
	else
	{
		en_a_retFunction = DIO_WRONG_INPUT;
	}
	return en_a_retFunction;
}
