/*
 * app.h
 *
 * Created: 10/4/2023 10:33:37 AM
 *  Author: mohamed mansour
 */ 


#ifndef APP_H_
#define APP_H_

/********************* INCLUDES SECTION ***********************/
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/dio/dio.h"
#include "../MCAL/exti/exti.h"
#include "../MCAL/gie/gie.h"
#include "../MCAL/timer/timer.h"
#include "../HAL/button/button.h"
#include "../HAL/led/led.h"
#include "../HAL/motor_driver/motor.h"

/***********************  MACROS DEFINITIONS ***********************/
#define SHORTEST_SIDE_PERIOD	4 /*  2 sec */
#define LONGEST_SIDE_PERIOD		6 /*  3 sec */
#define ROTATE_PERIOD			2 /*  1 sec */
#define SEQUENCE_MAX_NUMBER		4 /*  Array size */

/*********************** USER TYPES DEFINITION ***********************/

typedef enum {
	APP_OK = 0,
	APP_NOK,
	APP_WRONG_INPUT,
	
}en_appErrorStatus;

typedef struct
{
	en_appErrorStatus (* ptr_g_Function)(void);
	u8 period;
	
}st_carMode;

typedef enum 
{
	SYSTEM_ON = 0,
	SYSTEM_OFF,
	START_PRESSED,
	
}en_systemStatus;


/********************* FUNCTIONS PROTOTYPES  **********************/
en_appErrorStatus APP_init();
void APP_systemStart();
void APP_systemStop();
void APP_overflowRoutine();
void APP_pwmRoutine();
en_appErrorStatus APP_longestSide();
en_appErrorStatus APP_shortestSide();
en_appErrorStatus APP_rotate();
en_appErrorStatus APP_temporaryStop();



#endif /* APP_H_ */