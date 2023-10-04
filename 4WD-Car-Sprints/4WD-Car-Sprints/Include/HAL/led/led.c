/*
* led.c
*
*  Created on: Oct 13, 2023
*      Author: Mahmoud Mahran
*     Version: 0.1
*/
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/dio/dio.h"
#include "led.h"

en_ledError LED_init(st_leds *st_a_led)
{
	en_ledError en_a_retFunction = LED_OK;
	st_pinConfig st_a_ledPin = {st_a_led->port, st_a_led->pin, DIO_DIRECTION_OUTPUT, DIO_LOW};
	if (DIO_pinInit(&st_a_ledPin) == DIO_OK )
	{
		st_a_led->state = 0;
		en_a_retFunction = LED_OK;
		} else {
		en_a_retFunction = LED_OPERATION_FAILED;
	}
	return en_a_retFunction;
}
en_ledError LED_on(st_leds *st_a_led)
{
	en_ledError en_a_retFunction = LED_OK;
	st_pinConfig st_a_ledPin = {st_a_led->port, st_a_led->pin, DIO_DIRECTION_OUTPUT, DIO_HIGH};
	if (DIO_setPinStatus(&st_a_ledPin, DIO_HIGH) == DIO_OK)
	{
		st_a_led->state = 2;
		en_a_retFunction = LED_OK;
		} else {
		en_a_retFunction = LED_OPERATION_FAILED;
	}
	return en_a_retFunction;
}
en_ledError LED_off(st_leds *st_a_led)
{
	en_ledError en_a_retFunction = LED_OK;
	st_pinConfig st_a_ledPin = {st_a_led->port, st_a_led->pin, DIO_DIRECTION_OUTPUT, DIO_LOW};
	if (DIO_setPinStatus(&st_a_ledPin, DIO_LOW) == DIO_OK)
	{
		st_a_led->state = 1;
		en_a_retFunction = LED_OK;
		} else {
		en_a_retFunction = LED_OPERATION_FAILED;
	}
	return en_a_retFunction;
}
en_ledError LED_toggle(st_leds *st_a_led)
{
	en_ledError en_a_retFunction = LED_OK;
	st_pinConfig st_a_ledPin = {st_a_led->port, st_a_led->pin, DIO_DIRECTION_OUTPUT, DIO_LOW};
	if (DIO_togglePinStatus(&st_a_ledPin) == DIO_OK)
	{
		if(st_a_led->state == 1) st_a_led->state = 2;
		if(st_a_led->state == 2) st_a_led->state = 1;
		en_a_retFunction = LED_OK;
		} else {
		en_a_retFunction = LED_OPERATION_FAILED;
	}
	return en_a_retFunction;
	
}
