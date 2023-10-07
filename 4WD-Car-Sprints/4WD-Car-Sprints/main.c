/*
 * 4WD-Car-Sprints.c
 *
 * Created: 10/3/2023 2:00:33 PM
 * Author : 
 */ 




#include "Include/LIB/STD_TYPES.h"
#include "Include/APP/app.h"

/* Global variables */

// System status of the car
extern en_systemStatus en_g_carStatus;

// Half-second stop status
extern en_systemStatus u8_g_halfSecondStop;

// Array to store the sequence of car modes
extern st_carMode st_g_systemSequence[SEQUENCE_MAX_NUMBER];

// Current sequence number
extern u8 u8_g_sequenceNumber;

/************************************************************/
int main(void)
{
	// Initialize the application
	APP_init();
	
    while (1) 
    {
		// Check if the car system is ON
		if(en_g_carStatus == SYSTEM_ON)
		{
			// Check if the half-second stop is not active
			if(u8_g_halfSecondStop != 1)
			{
				// Execute the function specified by the current sequence number
				st_g_systemSequence[u8_g_sequenceNumber].ptr_g_Function();
			}
			else
			{
				// Temporarily stop the car
				APP_temporaryStop();
			}
		}
		else
		{
			// Car system is OFF, no action is taken
		}
    }
}