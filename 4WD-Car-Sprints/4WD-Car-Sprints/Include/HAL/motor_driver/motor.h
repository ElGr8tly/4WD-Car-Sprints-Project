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

en_motorErrorStatus MOTOR_driverInitialize();
en_motorErrorStatus MOTOR_leftMotorForwardDirection();
en_motorErrorStatus MOTOR_leftMotorBackwardDirection();
en_motorErrorStatus MOTOR_rightMotorForwardDirection();
en_motorErrorStatus MOTOR_rightMotorBackwardDirection();
en_motorErrorStatus MOTOR_stopMotorDirection();

#endif	/* MOTOR_DRIVER_L298N_H */

