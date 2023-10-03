/*
 * dio.c
 *
 * Created: 10/3/2023 2:08:45 PM
 *  Author: Elgreatly and Mansour
 */ 
#include "../../LIB/STD_TYPES.h"
#include "dio.h"
#define CATCH_RESERVED_BIT( _pin_ )       ((_pin_) >> 7)

/* Section: Function Declarations */


u8_returnType DIO_pinInit(const st_pinConfig *st_a_pinConfig)
{
	u8_returnType u8_a_retFunction = DIO_OK;
	if (st_a_pinConfig != NULL)
	{
		if (CATCH_RESERVED_BIT(st_a_pinConfig) == 0 )
		{
			u8_a_retFunction &= DIO_setPinDirection(st_a_pinConfig);
			u8_a_retFunction &= DIO_setPinStatus(st_a_pinConfig, st_a_pinConfig->logic);
		}
		else
		{
			u8_a_retFunction = DIO_WRONG_INPUT;
		}

	}
	else
	{
		u8_a_retFunction = DIO_WRONG_INPUT;
	}

	return u8_a_retFunction;
}
u8_returnType DIO_setPinDirection(const st_pinConfig *st_a_pinConfig){}//mansour
u8_returnType DIO_getPinDirection(const st_pinConfig *st_a_pinConfig, en_pinDirection *en_a_directionStatus){}//greatly
u8_returnType DIO_setPinStatus( st_pinConfig *st_a_pinConfig, en_bitLogic en_a_bitLogic){}//mansour
u8_returnType DIO_getPinStatus( st_pinConfig *st_a_pinConfig, en_bitLogic *en_a_bitLogic){}//greatly
u8_returnType DIO_togglePinStatus( st_pinConfig *st_a_pinConfig);//mansour