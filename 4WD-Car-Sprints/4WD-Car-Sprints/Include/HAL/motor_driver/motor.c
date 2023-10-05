/* 
 * File:   motor.c
 * Author: ElGreatly
 * Created on March 14, 2023 
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/dio/dio.h"
#include "Motor.h"
/**********************************************************************************************/
/* Section: Macro Declarations */
/*  */
#define MOTOR_PORT           PORTA_INDEX
#define MOTOR_PIN_1           DIO_PIN0
#define MOTOR_PIN_2           DIO_PIN1
#define MOTOR_PIN_3           DIO_PIN2
#define MOTOR_PIN_4           DIO_PIN3

/* Section: Global Variables */
st_pinConfig st_g_leftMotorDirectionControl [2] =
{
    
  { /*Pin D4*/
  .u8_g_port = MOTOR_PORT,
  .u8_g_pin = MOTOR_PIN_1,
  .u8_g_direction = DIO_DIRECTION_OUTPUT,
  .u8_g_logic = DIO_HIGH,        /* Default logic when set output direction */
  .u8_g_reserved = DIO_UNLOCK
  }
  ,
  { /*Pin D5*/
  .u8_g_port = MOTOR_PORT,
  .u8_g_pin = MOTOR_PIN_2,
  .u8_g_direction = DIO_DIRECTION_OUTPUT,
  .u8_g_logic = DIO_HIGH,        /* Default logic when set output direction */
  .u8_g_reserved = DIO_UNLOCK
  }
};
st_pinConfig st_g_rightMotorDirectionControl[2] =
{

  { /*Pin D6*/
  .u8_g_port = MOTOR_PORT,
  .u8_g_pin = MOTOR_PIN_3,
  .u8_g_direction = DIO_DIRECTION_OUTPUT,
  .u8_g_logic = DIO_HIGH,        /* Default logic when set output direction */
  .u8_g_reserved = DIO_UNLOCK
  }
  ,
  { /*Pin D7*/
  .u8_g_port = MOTOR_PORT,
  .u8_g_pin = MOTOR_PIN_4,
  .u8_g_direction = DIO_DIRECTION_OUTPUT,
  .u8_g_logic = DIO_HIGH,        /* Default logic when set output direction */
  .u8_g_reserved = DIO_UNLOCK
  }
};
/***********************************************************************************************/
/* Module APIs */
en_motorErrorStatus MOTOR_driverInitialize()
{
    en_motorErrorStatus   en_a_retFunction = MOTOR_OK;

    en_a_retFunction |= DIO_pinInitialize(&(st_g_leftMotorDirectionControl[0]));
    en_a_retFunction |= DIO_pinInitialize(&(st_g_leftMotorDirectionControl[1]));
    en_a_retFunction |= DIO_pinInitialize(&(st_g_rightMotorDirectionControl[0]));
    en_a_retFunction |= DIO_pinInitialize(&(st_g_rightMotorDirectionControl[1]));

    return en_a_retFunction;
}
en_motorErrorStatus MOTOR_leftMotorForwardDirection()
{
    en_motorErrorStatus   en_a_retFunction = MOTOR_OK;

    en_a_retFunction |= DIO_setPinStatus(&(st_g_leftMotorDirectionControl[0]), DIO_HIGH);
    en_a_retFunction |= DIO_setPinStatus(&(st_g_leftMotorDirectionControl[1]), DIO_LOW);

    return en_a_retFunction;
}
en_motorErrorStatus MOTOR_leftMotorBackwardDirection()
{
    en_motorErrorStatus   en_a_retFunction = MOTOR_OK;

    en_a_retFunction &= DIO_setPinStatus(&(st_g_leftMotorDirectionControl[0]), DIO_LOW);
    en_a_retFunction &= DIO_setPinStatus(&(st_g_leftMotorDirectionControl[1]), DIO_HIGH);

    return en_a_retFunction;
}
en_motorErrorStatus MOTOR_rightMotorForwardDirection()
{
    en_motorErrorStatus   en_a_retFunction = MOTOR_OK;

    en_a_retFunction &= DIO_setPinStatus(&(st_g_rightMotorDirectionControl[0]), DIO_HIGH);
    en_a_retFunction &= DIO_setPinStatus(&(st_g_rightMotorDirectionControl[1]), DIO_LOW);

    return en_a_retFunction;
}
en_motorErrorStatus MOTOR_rightMotorBackwardDirection()
{
    en_motorErrorStatus   en_a_retFunction = MOTOR_OK;

    en_a_retFunction &= DIO_setPinStatus(&(st_g_rightMotorDirectionControl[0]), DIO_LOW);
    en_a_retFunction &= DIO_setPinStatus(&(st_g_rightMotorDirectionControl[1]), DIO_HIGH);

    return en_a_retFunction;
}
en_motorErrorStatus MOTOR_stopMotorDirection()
{
    en_motorErrorStatus   en_a_retFunction = MOTOR_OK;


    en_a_retFunction &= DIO_setPinStatus(&(st_g_leftMotorDirectionControl[0]), DIO_HIGH);
    en_a_retFunction &= DIO_setPinStatus(&(st_g_leftMotorDirectionControl[1]), DIO_HIGH);
    en_a_retFunction &= DIO_setPinStatus(&(st_g_rightMotorDirectionControl[0]), DIO_HIGH);
    en_a_retFunction &= DIO_setPinStatus(&(st_g_rightMotorDirectionControl[1]), DIO_HIGH);

    return en_a_retFunction;
}