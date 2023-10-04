/*
* button.c
*
*  Created on: Oct 04, 2023
*      Author: Mahmoud Mahran
*     Version: 0.1
*/
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/dio/dio.h"
#include "button.h"


en_buttonError BUTTON_init(st_button *st_a_butt){
	en_buttonError en_a_retFunction = BUTTON_OK;
	st_pinConfig st_a_buttonPin = {st_a_butt->port, st_a_butt->pin, GPIO_DIRECTION_INPUT, GPIO_LOW};
	if(DIO_pinInit(&st_a_buttonPin) == DIO_OK){
		en_a_retFunction = BUTTON_OK;
	}
	en_a_retFunction = BUTTON_OP_FAILED;
	
	return en_a_retFunction;
}

en_buttonError BUTTON_getValue(st_button *st_a_butt, en_bitLogic *en_a_buttonValue){
	en_buttonError en_a_retFunction = BUTTON_OK;
	st_pinConfig st_a_buttonPin = {st_a_butt->port, st_a_butt->pin, GPIO_DIRECTION_INPUT, GPIO_LOW};
	if(DIO_getPinStatus(&st_a_buttonPin, en_a_buttonValue) == DIO_OK){
		en_a_retFunction = BUTTON_OK;
	}
	en_a_retFunction = BUTTON_OP_FAILED;

	return en_a_retFunction;
}

en_buttonError BUTTON_connectIPU(st_button *st_a_butt){
	en_buttonError en_a_retFunction = BUTTON_OK;
	st_pinConfig st_a_buttonPin = {st_a_butt->port, st_a_butt->pin, GPIO_DIRECTION_INPUT, GPIO_HIGH};
	if(DIO_setPinStatus(&st_a_buttonPin, GPIO_HIGH) == DIO_OK){
		en_a_retFunction = BUTTON_OK;
	}
	en_a_retFunction = BUTTON_OP_FAILED;

	return en_a_retFunction;
}
