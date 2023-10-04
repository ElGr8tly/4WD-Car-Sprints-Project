/*
* button.c
*
*  Created on: Oct 04, 2023
*      Author: Mahmoud Mahran
*     Version: 0.1
*/
/* Module features :

01- BUTTON_init
02- BUTTON_getValue
03- BUTTON_connectIPU
*/
/*
************************************************************************************************************************
Standard Types
************************************************************************************************************************
*/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


/*
************************************************************************************************************************
MCAL Components
************************************************************************************************************************
*/

#include "../../MCAL/dio/dio.h"
/*
************************************************************************************************************************
HAL Components
************************************************************************************************************************
*/

#include "button.h"


/*
************************************************************************************************************************
************************************************************************************************************************
************************************************************************************************************************
*/

/*
************************************************************************************************************************
Functions Implementation
************************************************************************************************************************
*/

/*
**************************************************************************************************************************
********************************************** 01 - BUTTON_init  *********************************************************

1-  function Description ->  initializes the the pin that the button is interfaced with
2-  Options : NA

3- Function Arguments : (A)  st_a_butt  : button struct containing it's port and pin

4- Function Return ->  en_buttonError :
            (A) BUTTON_OK          : executed successfully
            (B) BUTTON_WRONG_INPUT : wrong input in button struct
            (C) BUTTON_OP_FAILED   : DIO couldn't initialize the pin
**************************************************************************************************************************
**************************************************************************************************************************
*/
en_buttonError BUTTON_init(st_button *st_a_butt){
	en_buttonError en_a_retFunction = BUTTON_OK;
	if(st_a_butt->port < 4 && st_a_butt->pin < 8){
		st_pinConfig st_a_buttonPin = {st_a_butt->port, st_a_butt->pin, DIO_DIRECTION_INPUT, DIO_LOW};
		if(DIO_pinInit(&st_a_buttonPin) == DIO_OK){
			en_a_retFunction = BUTTON_OK;
			} else {
			en_a_retFunction = BUTTON_OP_FAILED;
		}
		} else {
		en_a_retFunction = BUTTON_WRONG_INPUT;
	}
	return en_a_retFunction;
}
/*
******************************************************************************************************************************
********************************************** 02 - BUTTON_getValue  *********************************************************

1-  function Description ->  reads the the pin value that the button is interfaced with
2-  Options : NA

3- Function Arguments : (A)  st_a_butt  : button struct containing it's port and pin

4- Function Return   ->  en_buttonError :
(A) BUTTON_OK          : executed successfully
(B) BUTTON_WRONG_INPUT : wrong input in button struct
(B) BUTTON_OP_FAILED   : DIO couldn't get the pin value
**************************************************************************************************************************
**************************************************************************************************************************
*/
en_buttonError BUTTON_getValue(st_button *st_a_butt, en_bitLogic *en_a_buttonValue){
	en_buttonError en_a_retFunction = BUTTON_OK;
	if(st_a_butt->port < 4 && st_a_butt->pin < 8){
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

en_buttonError BUTTON_connectIPU(st_button *st_a_butt){
	en_buttonError en_a_retFunction = BUTTON_OK;
	if(st_a_butt->port < 4 && st_a_butt->pin < 8){
		st_pinConfig st_a_buttonPin = {st_a_butt->port, st_a_butt->pin, DIO_DIRECTION_INPUT, DIO_HIGH};
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
