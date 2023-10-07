/*
 * app.h
 *
 * Created: 10/4/2023 10:33:37 AM
 *  Author: mohamed mansour
 */ 


#ifndef APP_H_
#define APP_H_

/********************* INCLUDES SECTION ***********************/

// Standard library includes
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

// Microcontroller Abstraction Layer (MCAL) includes
#include "../MCAL/dio/dio.h"
#include "../MCAL/exti/exti.h"
#include "../MCAL/gie/gie.h"
#include "../MCAL/timer/timer.h"

// Hardware Abstraction Layer (HAL) includes
#include "../HAL/button/button.h"
#include "../HAL/led/led.h"
#include "../HAL/motor_driver/motor.h"

/*********************** MACROS DEFINITIONS ***********************/
// Time periods for various robot actions (in seconds)
#define SHORTEST_SIDE_PERIOD	4 /* 2 seconds */
#define LONGEST_SIDE_PERIOD	    6 /* 3 seconds */
#define ROTATE_PERIOD		    2 /* 1 second */
#define SEQUENCE_MAX_NUMBER	    4 /* Array size */
//Timer preload values for dutyCycle speed change 
/*      FOR TIMER0           */
#define SPEED_50             128
#define SPEED_30             77
#define MAX_PRELOAD          255
//Timer preload values for 0.5 (system tick)
/*      FOR TIMER1           */
#define PRE_TICKS            3035
/*********************** USER TYPES DEFINITION ***********************/

// Custom error status enumeration for the application
typedef enum {
	APP_OK = 0,            // Operation successful
	APP_NOK,               // Operation failed
	APP_WRONG_INPUT,       // Incorrect input or configuration
	
} en_appErrorStatus;

// Structure to define the behavior of different robot modes
typedef struct {
	en_appErrorStatus (*ptr_g_Function)(void); // Pointer to a function for the mode
	u8 period;                                  // Time period for the mode (in seconds)
	
} st_carMode;

// Enumeration to represent the system status
typedef enum {
	SYSTEM_ON = 0,     // System is ON
	SYSTEM_OFF,        // System is OFF
	START_PRESSED,     // Start button is pressed
	
} en_systemStatus;

/********************* FUNCTIONS PROTOTYPES  **********************/

// Initialize the application and all necessary hardware components
en_appErrorStatus APP_init();

// Start the robot system
void APP_systemStart();

// Stop the robot system
void APP_systemStop();

// Overflow interrupt routine
void APP_overflowRoutine();

// PWM interrupt routine
void APP_pwmRoutine();

// Functions for different robot modes
en_appErrorStatus APP_longestSide();
en_appErrorStatus APP_shortestSide();
en_appErrorStatus APP_rotate();
en_appErrorStatus APP_temporaryStop();

#endif /* APP_H_ */