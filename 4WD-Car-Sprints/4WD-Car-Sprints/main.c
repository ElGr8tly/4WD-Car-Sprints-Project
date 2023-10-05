/*
 * 4WD-Car-Sprints.c
 *
 * Created: 10/3/2023 2:00:33 PM
 * Author : melgreatly
 */ 

#include "Include/APP/app.h"
extern en_systemStatus en_g_carStatus ;
extern en_systemStatus u8_g_halfSecondStop ;
u8 u8_g_pwmDutyCycle = 231;

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		if(en_g_carStatus == SYSTEM_ON)
		{
			if(u8_g_halfSecondStop == 1)
			{
				
			}
		}
    }
}

