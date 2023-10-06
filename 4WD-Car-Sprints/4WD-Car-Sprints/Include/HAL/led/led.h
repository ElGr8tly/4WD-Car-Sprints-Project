/*
*****************************************************************************************************************
    Author 		: Mahmoud Mahran
    Version		: V:1.0
	Date 		: 03/10/2023
Description 	: led.h --> Prototypes
*****************************************************************************************************************

What to sell for customer
	1- the Architecture of the API
	2- Name of the functions
	3- The outputs
	4- macros
*/

/*
*************************************************************************************************************************
*************************************************************************************************************************
**************************************************File Guard*************************************************************
*************************************************************************************************************************
*/
#ifndef LED_H_
#define LED_H_



///////////////ERROR type///////////////
typedef enum en_ledError{
	LED_OK,
	LED_WRONG_INPUT,
    LED_OPERATION_FAILED
}en_ledError;


///////////////LEDS struct///////////////
typedef struct st_leds{
	u8 port;
	u8 pin;
	u8 state;
}st_leds;
/*
*************************************************************************************************************************
*************************************************************************************************************************
**************************************************Function Prototypes*************************************************************
*************************************************************************************************************************
*/
/*function that takes a "LEDS" struct and returns an int for error handling
initializes led according to given arguments */
en_ledError LED_init(st_leds *st_a_led);
/*function that takes a "LEDS" struct and returns an int for error handling
turns on led */
en_ledError LED_on(st_leds *st_a_led);
/*function that takes a "LEDS" struct and returns an int for error handling
turns off led */
en_ledError LED_off(st_leds *st_a_led);
/*function that takes a "LEDS" struct and returns an int for error handling
toggles led */
en_ledError LED_toggle(st_leds *st_a_led);

#endif /* LED_H_ */
