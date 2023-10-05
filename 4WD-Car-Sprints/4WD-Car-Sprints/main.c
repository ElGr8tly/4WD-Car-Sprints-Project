/*
 * 4WD-Car-Sprints.c
 *
 * Created: 10/3/2023 2:00:33 PM
 * Author : melgreatly
 */ 

//#include <avr/io.h>
#include "Include/LIB/STD_TYPES.h"
#include "Include/APP/app.h"

/*global variables*/
extern en_systemStatus en_g_carStatus ;
extern en_systemStatus u8_g_halfSecondStop ;
extern st_carMode st_g_systemSequence[SEQUENCE_MAX_NUMBER];
extern u8 u8_g_sequenceNumber;

/************************************************************/
int main(void)
{
	//DIO_setPinDirection((st_pinConfig*){PORTC_INDEX,DIO_PIN7,DIO_DIRECTION_OUTPUT,DIO_HIGH,DIO_UNLOCK});
	//DIO_setPinStatus((st_pinConfig*){PORTC_INDEX,DIO_PIN7,DIO_DIRECTION_OUTPUT,DIO_HIGH,DIO_UNLOCK},DIO_HIGH);
	
	
	APP_init();
	//MOTOR_stopMotorDirection();
	//MOTOR_leftMotorForwardDirection();
	//MOTOR_rightMotorBackwardDirection();	
	//DIO_DDRA = 0xff;
	//DIO_PORTA = 0x15;

    while (1) 
    {
	
		if(en_g_carStatus == SYSTEM_ON)
		{
			if(u8_g_halfSecondStop != 1)
			{
				st_g_systemSequence[u8_g_sequenceNumber].ptr_g_Function();
			}
			else
			{
				APP_temporaryStop();
			}
		}
		else
		{
			
		}
    }
}

