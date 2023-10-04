/* 
 * File:   motor.c
 * Author: ElGreatly
 * Created on March 14, 2023 
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/dio/dio.h"
#include "Motor_Driver_L298N.h"
/**********************************************************************************************/
/* Section: Macro Declarations */
/*  */
#define MOTOR_PORT           PORTD_INDEX
#define MOTOR_PIN_1           DIO_PIN1
#define MOTOR_PIN_2           DIO_PIN2
#define MOTOR_PIN_3           DIO_PIN3
#define MOTOR_PIN_4           DIO_PIN4

/* Section: Global Variables */
st_pinConfig MOTOR_LeftMotorDirectionControl [2] =
{
    
  { /*Pin D4*/
  .u8_g_port = MOTOR_PORT,
  .u8_g_pin = MOTOR_PIN_1,
  .u8_g_direction = PIN_OUTPUT,
  .u8_g_logic = DIO_HIGH,        /* Default logic when set output direction */
  .u8_g_reserved = DIO_UNLOCK
  }
  ,
  { /*Pin D5*/
  .u8_g_port = MOTOR_PORT,
  .u8_g_pin = MOTOR_PIN_1,
  .u8_g_direction = PIN_OUTPUT,
  .u8_g_logic = DIO_HIGH,        /* Default logic when set output direction */
  .u8_g_reserved = DIO_UNLOCK
  }
};
st_pinConfig MOTOR_RightMotorDirectionControl[2] =
{

  { /*Pin D6*/
  .u8_g_port = MOTOR_PORT,
  .u8_g_pin = MOTOR_PIN_3,
  .u8_g_direction = PIN_OUTPUT,
  .u8_g_logic = DIO_HIGH,        /* Default logic when set output direction */
  .u8_g_reserved = DIO_UNLOCK
  }
  ,
  { /*Pin D7*/
  .u8_g_port = MOTOR_PORT,
  .u8_g_pin = MOTOR_PIN_4,
  .u8_g_direction = PIN_OUTPUT,
  .u8_g_logic = DIO_HIGH,        /* Default logic when set output direction */
  .u8_g_reserved = DIO_UNLOCK
  }
};
/***********************************************************************************************/
/* Module APIs */
en_motorErrorStatus MOTOR_DriverInitialize()
{
    en_motorErrorStatus   en_a_retFunction = MOTOR_OK;

    en_a_retFunction |= DIO_pinInitialize(&(MOTOR_LeftMotorDirectionControl[0]));
    en_a_retFunction |= DIO_pinInitialize(&(MOTOR_LeftMotorDirectionControl[1]));
    en_a_retFunction |= DIO_pinInitialize(&(MOTOR_RightMotorDirectionControl[0]));
    en_a_retFunction |= DIO_pinInitialize(&(MOTOR_RightMotorDirectionControl[1]));

    return en_a_retFunction;
}
en_motorErrorStatus MOTOR_LeftMotorForwardDirection()
{
    en_motorErrorStatus   en_a_retFunction = MOTOR_OK;

    en_a_retFunction |= DIO_setPinStatus(&(MOTOR_LeftMotorDirectionControl[0]), PIN_HIGH);
    en_a_retFunction |= DIO_setPinStatus(&(MOTOR_LeftMotorDirectionControl[1]), PIN_LOW);

    return en_a_retFunction;
}
en_motorErrorStatus MOTOR_LeftMotorBackwardDirection()
{
    en_motorErrorStatus   en_a_retFunction = MOTOR_OK;

    en_a_retFunction &= DIO_setPinStatus(&(MOTOR_LeftMotorDirectionControl[0]), PIN_LOW);
    en_a_retFunction &= DIO_setPinStatus(&(MOTOR_LeftMotorDirectionControl[1]), PIN_HIGH);

    return en_a_retFunction;
}
en_motorErrorStatus MOTOR_RightMotorForwardDirection()
{
    en_motorErrorStatus   en_a_retFunction = MOTOR_OK;

    en_a_retFunction &= DIO_setPinStatus(&(MOTOR_RightMotorDirectionControl[0]), PIN_HIGH);
    en_a_retFunction &= DIO_setPinStatus(&(MOTOR_RightMotorDirectionControl[1]), PIN_LOW);

    return execution_test;
}
en_motorErrorStatus MOTOR_RightMotorBackwardDirection()
{
    en_motorErrorStatus   en_a_retFunction = MOTOR_OK;

    en_a_retFunction &= DIO_setPinStatus(&(MOTOR_RightMotorDirectionControl[0]), PIN_LOW);
    en_a_retFunction &= DIO_setPinStatus(&(MOTOR_RightMotorDirectionControl[1]), PIN_HIGH);

    return en_a_retFunction;
}
en_motorErrorStatus MOTOR_StopMotorDirection()
{
    en_motorErrorStatus   en_a_retFunction = MOTOR_OK;


    en_a_retFunction &= DIO_setPinStatus(&(MOTOR_RightMotorDirectionControl[0]), PIN_HIGH);
    en_a_retFunction &= DIO_setPinStatus(&(MOTOR_RightMotorDirectionControl[1]), PIN_HIGH);
    en_a_retFunction &= DIO_setPinStatus(&(MOTOR_RightMotorDirectionControl[0]), PIN_HIGH);
    en_a_retFunction &= DIO_setPinStatus(&(MOTOR_RightMotorDirectionControl[1]), PIN_HIGH);

    return en_a_retFunction;
}