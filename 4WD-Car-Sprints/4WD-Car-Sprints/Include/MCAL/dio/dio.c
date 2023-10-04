/*
 * dio.c
 *  Created: 10/3/2023 2:08:45 PM
 *  Author: Elgreatly and Mansour
 */ 
#include "../../LIB/STD_TYPES.h"
#include "dio.h"

/* Section: Function Definitions */

/******************************************************************************/
/* Function: DIO_pinInit    @written by: Mohamed El-Greatly                   */
/* I/P Parameters: st_pinConfig,								                          	  */
/* Returns: en_dioErrorStatus				                                  			  */
/* Desc: This Function initialize a given pin				                      	  */
/******************************************************************************/
/* Options														                                			  */
/******************************************************************************/
/* port     : port0..3												                          		  */	
/* pin      : pin0 ..7       									                            	  */
/* direction: 0 or 1		        		                      	            		  */
/* logic    : 0 or 1 if direction = 0                                         */
/******************************************************************************/
en_dioErrorStatus DIO_pinInit(const st_pinConfig *st_a_pinConfig)
{
	en_dioErrorStatus en_a_retFunction = DIO_OK;
	if (st_a_pinConfig != NULL)
	{
		if (st_a_pinConfig->u8_g_reserved == 0 )
		{
			en_a_retFunction &= DIO_setPinDirection(st_a_pinConfig);
			en_a_retFunction &= DIO_setPinStatus(st_a_pinConfig, st_a_pinConfig->u8_g_logic);
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
en_dioErrorStatus DIO_setPinDirection(const st_pinConfig *st_a_pinConfig)
{
	en_dioErrorStatus en_a_retFunction =  DIO_OK;
	if (st_a_pinConfig != NULL)
	{
		if (st_a_pinConfig->u8_g_reserved == 0 )
		{
		
	 switch(st_a_pinConfig->u8_g_port)
	 {
		case PORTA_INDEX:
			if(st_a_pinConfig->u8_g_direction == DIO_DIRECTION_INPUT)
			{
				CLR_BIT(DIO_DDRA,st_a_pinConfig->u8_g_pin);
			}
			else
			{
				SET_BIT(DIO_DDRA,st_a_pinConfig->u8_g_pin);
			}
		break;
		case PORTB_INDEX:
		if(st_a_pinConfig->u8_g_direction == DIO_DIRECTION_INPUT)
		{
			CLR_BIT(DIO_DDRB,st_a_pinConfig->u8_g_pin);
		}
		else
		{
			SET_BIT(DIO_DDRB,st_a_pinConfig->u8_g_pin);
		}
		break;
		case PORTC_INDEX:
		if(st_a_pinConfig->u8_g_direction == DIO_DIRECTION_INPUT)
		{
			CLR_BIT(DIO_DDRC,st_a_pinConfig->u8_g_pin);
		}
		else
		{
			SET_BIT(DIO_DDRC,st_a_pinConfig->u8_g_pin);
		}
		break;
		case PORTD_INDEX:
		if(st_a_pinConfig->u8_g_direction == DIO_DIRECTION_INPUT)
		{
			CLR_BIT(DIO_DDRD,st_a_pinConfig->u8_g_pin);
		}
		else
		{
			SET_BIT(DIO_DDRD,st_a_pinConfig->u8_g_pin);
		}
		break;
		
	}
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

en_dioErrorStatus DIO_getPinDirection(const st_pinConfig *st_a_pinConfig, en_pinDirection *en_a_directionStatus){}

en_dioErrorStatus DIO_setPinStatus( st_pinConfig *st_a_pinConfig, en_bitLogic en_a_bitLogic)
{
		en_dioErrorStatus en_a_retFunction =  DIO_OK;
	if (st_a_pinConfig != NULL )
	{
		if (st_a_pinConfig->u8_g_reserved == 0 )
		{
		
			en_a_bitLogic &= 1 ;
      
			switch(st_a_pinConfig->u8_g_port)
			{
				case PORTA_INDEX:
          if(GET_BIT(DIO_DDRA,st_a_pinConfig->u8_g_pin) ==  DIO_DIRECTION_INPUT )
          {
            en_a_retFunction = DIO_NOK;
          }
          else
          {
				if(en_a_bitLogic == DIO_LOW)
				{
					CLR_BIT(DIO_PORTA,st_a_pinConfig->u8_g_pin);
          st_a_pinConfig->u8_g_logic = DIO_LOW;
				}
				else
				{
					SET_BIT(DIO_PORTA,st_a_pinConfig->u8_g_pin);
          st_a_pinConfig->u8_g_logic = DIO_HIGH;
				}
          }
				break;
          
				case PORTB_INDEX:
                    if(GET_BIT(DIO_DDRB,st_a_pinConfig->u8_g_pin) ==  DIO_DIRECTION_INPUT )
          {
            en_a_retFunction = DIO_NOK;
          }
          else
          {
				if(en_a_bitLogic == DIO_LOW)
				{
					CLR_BIT(DIO_PORTB,st_a_pinConfig->u8_g_pin);
          st_a_pinConfig->u8_g_logic = DIO_LOW;
				}
				else
				{
					SET_BIT(DIO_PORTB,st_a_pinConfig->u8_g_pin);
          st_a_pinConfig->u8_g_logic = DIO_HIGH;
				}
          }
				break;
            
				case PORTC_INDEX:
                    if(GET_BIT(DIO_DDRC,st_a_pinConfig->u8_g_pin) ==  DIO_DIRECTION_INPUT )
          {
            en_a_retFunction = DIO_NOK;
          }
          else
          {
				if(en_a_bitLogic == DIO_LOW)
				{
					CLR_BIT(DIO_PORTC,st_a_pinConfig->u8_g_pin);
          st_a_pinConfig->u8_g_logic = DIO_LOW;
				}
				else
				{
					SET_BIT(DIO_PORTC,st_a_pinConfig->u8_g_pin);
          st_a_pinConfig->u8_g_logic = DIO_HIGH;
				}
          }
				break;
            
				case PORTD_INDEX:
                   if(GET_BIT(DIO_DDRD,st_a_pinConfig->u8_g_pin) ==  DIO_DIRECTION_INPUT )
          {
            en_a_retFunction = DIO_NOK;
          }
          else
          {   
				if(en_a_bitLogic == DIO_LOW)
				{
					CLR_BIT(DIO_PORTD,st_a_pinConfig->u8_g_pin);
          st_a_pinConfig->u8_g_logic = DIO_LOW;
				}
				else
				{
					SET_BIT(DIO_PORTD,st_a_pinConfig->u8_g_pin);
          st_a_pinConfig->u8_g_logic = DIO_HIGH;
				}
          }
				break;
      }
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

en_dioErrorStatus DIO_getPinStatus( st_pinConfig *st_a_pinConfig, en_bitLogic *en_a_bitLogic){}//greatly

en_dioErrorStatus DIO_togglePinStatus( st_pinConfig *st_a_pinConfig)
{
		en_dioErrorStatus en_a_retFunction =  DIO_OK;
    en_bitLogic en_a_bitLogic = DIO_HIGH ;
	if (st_a_pinConfig != NULL )
	{
		if (st_a_pinConfig->u8_g_reserved == 0 )
		{
		
				en_a_retFunction = DIO_getPinStatus(st_a_pinConfig , &en_a_bitLogic) ;
        if(en_a_retFunction == DIO_OK )
        {
           en_a_bitLogic ^= 1 ;
				   en_a_retFunction = DIO_setPinStatus(st_a_pinConfig,en_a_bitLogic);
				}
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

