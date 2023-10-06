/*
 * 4wd-car-sprints.c
 *
 * created: 10/3/2023 2:00:33 pm
 * author : melgreatly
 */ 

//#include <avr/io.h>
#include "include/lib/std_types.h"
#include "include/app/app.h"

/*global variables*/
extern en_systemStatus en_g_carStatus ;
extern en_systemStatus u8_g_halfSecondStop ;
extern st_carMode st_g_systemSequence[SEQUENCE_MAX_NUMBER];
extern u8 u8_g_sequenceNumber;

/************************************************************/
int main(void)
{
	//dio_setpindirection((st_pinconfig*){portc_index,dio_pin7,dio_direction_output,dio_high,dio_unlock});
	//dio_setpinstatus((st_pinconfig*){portc_index,dio_pin7,dio_direction_output,dio_high,dio_unlock},dio_high);
	
	
	APP_init();
	//motor_stopmotordirection();
	//motor_leftmotorforwarddirection();
	//motor_rightmotorbackwarddirection();	
	//dio_ddra = 0xff;
	//dio_porta = 0x15;

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

