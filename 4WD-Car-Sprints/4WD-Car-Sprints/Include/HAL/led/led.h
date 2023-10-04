/*
* led.h
*
*  Created on: Oct 03, 2023
*      Author: Mahmoud Mahran
*     Version: 0.1
*/
#ifndef LED_H_
#define LED_H_
// error type
typedef enum en_ledError{
	LED_OK,
    LED_OPERATION_FAILED
}en_ledError;
//struct to store led attributes
typedef struct st_leds{
	u8 port;
	u8 pin;
	u8 state;
}st_leds;
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
