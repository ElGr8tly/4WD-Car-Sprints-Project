/*
* button.c
*
*  Created on: Oct 04, 2023
*      Author: msharfeldin
*     Version: 0.1
*/

/***************************** INCLUDES SECTION ***********************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/dio/dio.h"
#include "button.h"


/************************* FUNCTIONS DEFINEITIONS SECTION *****************************/

/*****************************************************************************/
/* Function: BUTTON_init    @written by: Mahmoud Sharf-Eldin				 */
/* I/P Parameters: st_button pointer										 */
/* Returns: en_buttonError				                                     */
/* Description: This Function initialize a pin to connect button on it       */
/*****************************************************************************/
/* Options														             */
/*****************************************************************************/
/* port     : PORTA....PORTD                                                 */
/* pin      : PIN0....PIN7        						                     */
/*****************************************************************************/

en_buttonError BUTTON_init(st_button *st_a_butt){
	en_buttonError en_a_retFunction = BUTTON_OK;
	if(st_a_butt->port <= MAX_PORT_INDEX && st_a_butt->pin <= MAX_PIN_INDEX){
		st_pinConfig st_a_buttonPin = {st_a_butt->port, st_a_butt->pin, DIO_DIRECTION_INPUT, DIO_LOW,DIO_UNLOCK};
		if(DIO_pinInitialize(&st_a_buttonPin) == DIO_OK)
		{
			en_a_retFunction = BUTTON_OK;
		} 
		else {
			en_a_retFunction = BUTTON_OP_FAILED;
		}
	} 
	else {
		en_a_retFunction = BUTTON_WRONG_INPUT;
	}
	return en_a_retFunction;
}
/*****************************************************************************/
/* Function: BUTTON_getValue    @written by: Mahmoud Sharf-Eldin			 */
/* I/P Parameters: st_button pointer, u8 *u8_a_buttonValue					 */
/* Returns: en_buttonError				                                     */
/* Description: This Function get value of connected button                  */
/*****************************************************************************/
/* Options														             */
/*****************************************************************************/
/* port     : PORTA....PORTD                                                 */
/* pin      : PIN0....PIN7        						                     */
/*****************************************************************************/
en_buttonError BUTTON_getValue(st_button *st_a_butt, en_bitLogic *en_a_buttonValue){
	en_buttonError en_a_retFunction = BUTTON_OK;
	if(st_a_butt->port <= MAX_PORT_INDEX && st_a_butt->pin <= MAX_PIN_INDEX ){
		st_pinConfig st_a_buttonPin = {st_a_butt->port, st_a_butt->pin, DIO_DIRECTION_INPUT, DIO_LOW};
		if(DIO_getPinStatus(&st_a_buttonPin, en_a_buttonValue) == DIO_OK){
			en_a_retFunction = BUTTON_OK;
			} else {
			en_a_retFunction = BUTTON_OP_FAILED;
		}
		} else {
		en_a_retFunction = BUTTON_WRONG_INPUT;
	}
	return en_a_retFunction;
}

/*****************************************************************************/
/* Function: BUTTON_connectIPU    @written by: Mahmoud Sharf-Eldin			 */
/* I/P Parameters: st_button pointer                     					 */
/* Returns: en_buttonError				                                     */
/* Description: This Function configure a pin to be connected to internal    */
/* pull-up resistor.                                                         */
/*****************************************************************************/
/* Options														             */
/*****************************************************************************/
/* port     : PORTA....PORTD                                                 */
/* pin      : PIN0....PIN7        						                     */
/*****************************************************************************/

en_buttonError BUTTON_connectIPU(st_button *st_a_butt){
	en_buttonError en_a_retFunction = BUTTON_OK;
	if(st_a_butt->port <= MAX_PORT_INDEX && st_a_butt->pin <= MAX_PIN_INDEX ){
		st_pinConfig st_a_buttonPin = {st_a_butt->port, st_a_butt->pin, DIO_DIRECTION_INPUT, DIO_HIGH,DIO_UNLOCK};
		if(DIO_setPinStatus(&st_a_buttonPin, DIO_HIGH) == DIO_OK){
			en_a_retFunction = BUTTON_OK;
			} else {
			en_a_retFunction = BUTTON_OP_FAILED;
		}
		} else {
		en_a_retFunction = BUTTON_WRONG_INPUT;
	}
	return en_a_retFunction;
}
