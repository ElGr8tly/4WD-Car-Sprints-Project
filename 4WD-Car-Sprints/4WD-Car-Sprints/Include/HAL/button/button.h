/*
 * button.h
 *
 *  Created on: Oct 04, 2023
 *      Author: Mahmoud Mahran
 *     Version: 0.1
 */
#ifndef BUTTON_H
#define BUTTON_H

typedef enum en_buttonError{
BUTTON_OK,
BUTTON_WRONG_INPUT,
BUTTON_OP_FAILED
}en_buttonError;

typedef struct st_button{
	u8 port;
	u8 pin;
}st_button;

en_buttonError BUTTON_init(st_button *st_a_butt);
en_buttonError BUTTON_getValue(st_button *st_a_butt, u8 *u8_a_buttonValue);
en_buttonError BUTTON_connectIPU(st_button *st_a_butt);

#endif
