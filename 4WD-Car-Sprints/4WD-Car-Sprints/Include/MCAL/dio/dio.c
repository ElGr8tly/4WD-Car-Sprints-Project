/*
 * dio.c
 *
 * Created: 10/3/2023 2:08:45 PM
 *  Author: Elgreatly and Mansour
 */ 
#include "../../LIB/STD_TYPES.h"
#include "dio.h"
/* Section: Function Declarations */
u8_returnType DIO_pinInit(const st_pinConfig *st_a_pinConfig)
{}//greatly
	
/******************************************************************************/
/* Function: DIO_setPinDirection                        					  */
/* I/P Parameters: st_pinConfig,								          	  */
/* Returns:u8_returnType				                                				  */
/* Desc:This Function Sets the direction of a given pin				       	  */
/******************************************************************************/
/* Options																	  */
/******************************************************************************/
/* port     : port0..3														  */	
/* pin      : pin0 ..7       									        	  */
/* directio: direction 0 or 1				                      			  */
/******************************************************************************/
u8_returnType DIO_setPinDirection(const st_pinConfig *st_a_pinConfig)
{
	u8_returnType u8_a_retFunction =  ERROR_OK;
	if(st_a_pinConfig->pin > 7 || st_a_pinConfig->pin < 0 || st_a_pinConfig->port < 0 || st_a_pinConfig->port > 3 || st_a_pinConfig ->direction > 1 || st_a_pinConfig->direction < 0)
	{
		u8_a_retFunction = ERROR_NOK;
	}
	else
	{
		
	switch(st_a_pinConfig->port)
	{
		case PORTA_INDEX:
			if(st_a_pinConfig->direction == DIO_DIRECTION_INPUT)
			{
				CLR_BIT(DIO_DDRA,st_a_pinConfig->pin);
			}
			else
			{
				SET_BIT(DIO_DDRA,st_a_pinConfig->pin);
			}
		break;
		case PORTB_INDEX:
		if(st_a_pinConfig->direction == DIO_DIRECTION_INPUT)
		{
			CLR_BIT(DIO_DDRB,st_a_pinConfig->pin);
		}
		else
		{
			SET_BIT(DIO_DDRB,st_a_pinConfig->pin);
		}
		break;
		case PORTC_INDEX:
		if(st_a_pinConfig->direction == DIO_DIRECTION_INPUT)
		{
			CLR_BIT(DIO_DDRC,st_a_pinConfig->pin);
		}
		else
		{
			SET_BIT(DIO_DDRC,st_a_pinConfig->pin);
		}
		break;
		case PORTD_INDEX:
		if(st_a_pinConfig->direction == DIO_DIRECTION_INPUT)
		{
			CLR_BIT(DIO_DDRD,st_a_pinConfig->pin);
		}
		else
		{
			SET_BIT(DIO_DDRD,st_a_pinConfig->pin);
		}
		break;
		
	}
	return u8_a_retFunction;
}//mansour
u8_returnType DIO_getPinDirection(const st_pinConfig *st_a_pinConfig, en_pinDirection *en_a_directionStatus){}//greatly
u8_returnType DIO_setPinStatus( st_pinConfig *st_a_pinConfig, en_bitLogic en_a_bitLogic)
{
		u8_returnType u8_a_retFunction =  ERROR_OK;
		if(st_a_pinConfig->direction == 0||st_a_pinConfig->pin > 7 || st_a_pinConfig->pin < 0 || st_a_pinConfig->port < 0 || st_a_pinConfig->port > 3 || st_a_pinConfig ->direction > 1 || st_a_pinConfig->direction < 0)
		{
			u8_a_retFunction = ERROR_NOK;
		}
		else
		{
			
			switch(st_a_pinConfig->port)
			{
				case PORTA_INDEX:
				if(st_a_pinConfig->logic == DIO_LOW)
				{
					CLR_BIT(DIO_PORTA,st_a_pinConfig->pin);
				}
				else
				{
					SET_BIT(DIO_PORTA,st_a_pinConfig->pin);
				}
				break;
				case PORTB_INDEX:
				if(st_a_pinConfig->logic == DIO_LOW)
				{
					CLR_BIT(DIO_PORTB,st_a_pinConfig->pin);
				}
				else
				{
					SET_BIT(DIO_PORTB,st_a_pinConfig->pin);
				}
				break;
				case PORTC_INDEX:
				if(st_a_pinConfig->logic == DIO_LOW)
				{
					CLR_BIT(DIO_PORTC,st_a_pinConfig->pin);
				}
				else
				{
					SET_BIT(DIO_PORTC,st_a_pinConfig->pin);
				}
				break;
				case PORTD_INDEX:
				if(st_a_pinConfig->logic == DIO_LOW)
				{
					CLR_BIT(DIO_PORTD,st_a_pinConfig->pin);
				}
				else
				{
					SET_BIT(DIO_PORTD,st_a_pinConfig->pin);
				}
				break;
				
			}
			return u8_a_retFunction;
}//mansour
u8_returnType DIO_getPinStatus( st_pinConfig *st_a_pinConfig, en_bitLogic *en_a_bitLogic){}//greatly
u8_returnType DIO_togglePinStatus( st_pinConfig *st_a_pinConfig)
{
			u8_returnType u8_a_retFunction =  ERROR_OK;
			if(st_a_pinConfig->direction == 0||st_a_pinConfig->pin > 7 || st_a_pinConfig->pin < 0 || st_a_pinConfig->port < 0 || st_a_pinConfig->port > 3 || st_a_pinConfig ->direction > 1 || st_a_pinConfig->direction < 0)
			{
				u8_a_retFunction = ERROR_NOK;
			}
			else
			{
				st_a_pinConfig->logic = st_a_pinConfig->logic == DIO_LOW?1:0
				switch(st_a_pinConfig->port)
				{
					case PORTA_INDEX:
					if(st_a_pinConfig->logic == DIO_HIGH)
					{
						CLR_BIT(DIO_PORTA,st_a_pinConfig->pin);
					}
					else
					{
						SET_BIT(DIO_PORTA,st_a_pinConfig->pin);
					}
					break;
					case PORTB_INDEX:
					if(st_a_pinConfig->logic == DIO_HIGH)
					{
						CLR_BIT(DIO_PORTB,st_a_pinConfig->pin);
					}
					else
					{
						SET_BIT(DIO_PORTB,st_a_pinConfig->pin);
					}
					break;
					case PORTC_INDEX:
					if(st_a_pinConfig->logic == DIO_HIGH)
					{
						CLR_BIT(DIO_PORTC,st_a_pinConfig->pin);
					}
					else
					{
						SET_BIT(DIO_PORTC,st_a_pinConfig->pin);
					}
					break;
					case PORTD_INDEX:
					if(st_a_pinConfig->logic == DIO_HIGH)
					{
						CLR_BIT(DIO_PORTD,st_a_pinConfig->pin);
					}
					else
					{
						SET_BIT(DIO_PORTD,st_a_pinConfig->pin);
					}
					break;
					
				}
				return u8_a_retFunction;
}//mansour