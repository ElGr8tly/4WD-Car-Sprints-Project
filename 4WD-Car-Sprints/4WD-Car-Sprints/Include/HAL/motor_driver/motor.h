/* 
 * File:   motor.h
 * Author: ElGreatly
 * Created on March 14, 2023 
 */

#ifndef MOTOR_DRIVER_L298N_H
#define	MOTOR_DRIVER_L298N_H

/* Section: Data Type Declarations */

typedef enum {
    MOTOR_OK = 0,
    MOTOR_NOK,
    MOTOR_WRONG_INPUT,
}en_motorErrorStatus;

/* Section : Function Declarations */

en_motorErrorStatus MOTOR_DriverInitialize();
en_motorErrorStatus MOTOR_LeftMotorForwardDirection();
en_motorErrorStatus MOTOR_LeftMotorBackwardDirection();
en_motorErrorStatus MOTOR_RightMotorForwardDirection();
en_motorErrorStatus MOTOR_RightMotorBackwardDirection();
en_motorErrorStatus MOTOR_StopMotorDirection();

#endif	/* MOTOR_DRIVER_L298N_H */

