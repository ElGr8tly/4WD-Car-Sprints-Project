/******************************************************************************************************************
    Author 		    : Mahmoud Mahran
	Version		    : V:1.0
	Date 		    : 03/10/2023
    Description     : led.c  ->  Implementation
  
    Module features :

						01- LED_init
						02- LED_on
						03- LED_off
						04- LED_toggle
						
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
#include "led.h"

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
********************************************** 01 - LED_init  **********************************************************

	1-  function Description ->  - Takes a "LEDS" struct and returns an error state.
	                             - Initializes led according to given arguments.
	2-  Options : NA
				  
	3- Function Arguments : (st_leds*) a struct that contains a port and a pin for the led ( ex : {PORTA_INDEX, DIO_PIN0} )
	
	4- Function Return   -> (en_ledError) error state (ex : LED_OK , LED_WRONG_INPUT, LED_OPERATION_FAILED ..) 
	
**************************************************************************************************************************
**************************************************************************************************************************	
*/
en_ledError LED_init(st_leds *st_a_led)
{
	en_ledError en_a_retFunction = LED_OK;
	if(st_a_led->port < 4 && st_a_led->pin < 8){
		st_pinConfig st_a_ledPin = {st_a_led->port, st_a_led->pin, DIO_DIRECTION_OUTPUT, DIO_LOW};
		if (DIO_pinInitialize(&st_a_ledPin) == DIO_OK )
		{
			st_a_led->state = 0;
			en_a_retFunction = LED_OK;
			} else {
			en_a_retFunction = LED_OPERATION_FAILED;
		}
		} else {
		en_a_retFunction = LED_WRONG_INPUT;
	}
	return en_a_retFunction;
}
/*
**************************************************************************************************************************
********************************************** 02 - LED_on  **********************************************************

	1-  function Description ->  - Takes a "LEDS" struct and returns an error state.
	                             - Turns on led.
	2-  Options : NA
				  
	3- Function Arguments : (st_leds*) a struct that contains a port and a pin for the led ( ex : {PORTA_INDEX, DIO_PIN0} )
	
	4- Function Return   -> (en_ledError) error state (ex : LED_OK , LED_WRONG_INPUT, LED_OPERATION_FAILED ..) 
	
**************************************************************************************************************************
**************************************************************************************************************************	
*/
en_ledError LED_on(st_leds *st_a_led)
{
	en_ledError en_a_retFunction = LED_OK;
	if(st_a_led->port < 4 && st_a_led->pin < 8){
		st_pinConfig st_a_ledPin = {st_a_led->port, st_a_led->pin, DIO_DIRECTION_OUTPUT, DIO_HIGH};
		if (DIO_setPinStatus(&st_a_ledPin, DIO_HIGH) == DIO_OK)
		{
			st_a_led->state = 2;
			en_a_retFunction = LED_OK;
			} else {
			en_a_retFunction = LED_OPERATION_FAILED;
		}
		} else {
		en_a_retFunction = LED_WRONG_INPUT;
	}
	return en_a_retFunction;
}
/*
**************************************************************************************************************************
********************************************** 03 - LED_off  **********************************************************

	1-  function Description ->  - Takes a "LEDS" struct and returns an error state.
	                             - Turns off led.
	2-  Options : NA
				  
	3- Function Arguments : (st_leds*) a struct that contains a port and a pin for the led ( ex : {PORTA_INDEX, DIO_PIN0} )
	
	4- Function Return   -> (en_ledError) error state (ex : LED_OK , LED_WRONG_INPUT, LED_OPERATION_FAILED ..) 
	
**************************************************************************************************************************
**************************************************************************************************************************	
*/
en_ledError LED_off(st_leds *st_a_led)
{
	en_ledError en_a_retFunction = LED_OK;
	if(st_a_led->port < 4 && st_a_led->pin < 8){
		st_pinConfig st_a_ledPin = {st_a_led->port, st_a_led->pin, DIO_DIRECTION_OUTPUT, DIO_LOW};
		if (DIO_setPinStatus(&st_a_ledPin, DIO_LOW) == DIO_OK)
		{
			st_a_led->state = 1;
			en_a_retFunction = LED_OK;
			} else {
			en_a_retFunction = LED_OPERATION_FAILED;
		}
		} else {
		en_a_retFunction = LED_WRONG_INPUT;
	}
	return en_a_retFunction;
}
/*
**************************************************************************************************************************
********************************************** 04 - LED_toggle  **********************************************************

	1-  function Description ->  - Takes a "LEDS" struct and returns an error state.
	                             - Toggles led.
	2-  Options : NA
				  
	3- Function Arguments : (st_leds*) a struct that contains a port and a pin for the led ( ex : {PORTA_INDEX, DIO_PIN0} )
	
	4- Function Return   -> (en_ledError) error state (ex : LED_OK , LED_WRONG_INPUT, LED_OPERATION_FAILED ..) 
	
**************************************************************************************************************************
**************************************************************************************************************************	
*/
en_ledError LED_toggle(st_leds *st_a_led)
{
	en_ledError en_a_retFunction = LED_OK;
	if(st_a_led->port < 4 && st_a_led->pin < 8){
		st_pinConfig st_a_ledPin = {st_a_led->port, st_a_led->pin, DIO_DIRECTION_OUTPUT, DIO_LOW};
		if (DIO_togglePinStatus(&st_a_ledPin) == DIO_OK)
		{
			if(st_a_led->state == 1) st_a_led->state = 2;
			if(st_a_led->state == 2) st_a_led->state = 1;
			en_a_retFunction = LED_OK;
			} else {
			en_a_retFunction = LED_OPERATION_FAILED;
		}
		} else {
		en_a_retFunction = LED_WRONG_INPUT;
	}
	return en_a_retFunction;
	
}
