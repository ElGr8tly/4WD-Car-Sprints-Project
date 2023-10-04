/*
 * dio.c
 *
 * Created: 10/3/2023 2:08:45 PM
 *  Author: Elgreatly and Mansour
 */ 
#include "../../LIB/STD_TYPES.h"
#include "dio.h"

/* Section: Function Definitions */


en_dioErrorStatus DIO_pinInit(const st_pinConfig *st_a_pinConfig)
{
	en_dioErrorStatus en_a_retFunction = DIO_OK;
	if (st_a_pinConfig != NULL)
	{
		if (st_a_pinConfig->u8_g_reserved == 0 )
		{
			en_a_retFunction &= DIO_setPinDirection(st_a_pinConfig);
			en_a_retFunction &= DIO_setPinStatus(st_a_pinConfig, st_a_pinConfig->logic);
		}
		else  /* Wrong data casted to pinConfig struct */
		{
			en_a_retFunction = DIO_WRONG_INPUT;
		}

	}
	else
	{
		en_a_retFunction = DIO_WRONG_INPUT;
	}

	return en_a_retFunction;
}
en_dioErrorStatus DIO_setPinDirection(const st_pinConfig *st_a_pinConfig){}//mansour
en_dioErrorStatus DIO_getPinDirection(const st_pinConfig *st_a_pinConfig, en_pinDirection *en_a_directionStatus){}//greatly
en_dioErrorStatus DIO_setPinStatus( st_pinConfig *st_a_pinConfig, en_bitLogic en_a_bitLogic){}//mansour
en_dioErrorStatus DIO_getPinStatus( st_pinConfig *st_a_pinConfig, en_bitLogic *en_a_bitLogic){}//greatly
en_dioErrorStatus DIO_togglePinStatus( st_pinConfig *st_a_pinConfig);//mansour