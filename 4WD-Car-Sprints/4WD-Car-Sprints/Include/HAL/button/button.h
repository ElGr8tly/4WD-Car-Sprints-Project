/*
 * button.h
 *
 *  Created on: Oct 04, 2023
 *      Author: msharfeldin
 *     Version: 0.1
 */
#ifndef BUTTON_H
#define BUTTON_H


/****************************** MACROS DEFINITION SECTION ****************************/

#define MAX_PORT_INDEX   3
#define MAX_PIN_INDEX    7

/************************** USER DEFINED PROTOTYPES SECTION ************************/


typedef enum en_buttonError{
BUTTON_OK,
BUTTON_WRONG_INPUT,
BUTTON_OP_FAILED
}en_buttonError;

typedef struct st_button{
	u8 port;
	u8 pin;
}st_button;

/************************** FUNCTION DECLARATION ************************/

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

en_buttonError BUTTON_init(st_button *st_a_butt);

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

en_buttonError BUTTON_getValue(st_button *st_a_butt, u8 *u8_a_buttonValue);

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

en_buttonError BUTTON_connectIPU(st_button *st_a_butt);

#endif
