/*
* app.c
*
* Created: 10/3/2023 2:11:11 PM
*  Author:
*/
/********************* INCLUDES SECTION ***********************/
#include "app.h"

/******************** GLOBAL VARIABLES DEFINETIONS *******************/

en_systemStatus en_g_carStatus = SYSTEM_OFF; // Variable to track the system status (ON/OFF)

u8 u8_g_sequenceNumber = 0; // Counter to keep track of the current sequence number

u8 u8_g_halfSecondStop = 0; // Counter for half-second stop

u8 u8_g_pwmDutyCycle = 128; // PWM duty cycle value

u16 u16_g_timerLastValue = 0; // Last recorded timer value

st_leds *st_g_currentLed; // Pointer to the currently active LED

// Array of sequences defining robot actions with associated functions and periods
st_carMode st_g_systemSequence[SEQUENCE_MAX_NUMBER] = {
	{
		.ptr_g_Function = APP_longestSide,
		.period = LONGEST_SIDE_PERIOD
	},
	{
		.ptr_g_Function = APP_rotate,
		.period = ROTATE_PERIOD
	},
	{
		.ptr_g_Function = APP_shortestSide,
		.period = SHORTEST_SIDE_PERIOD
	},
	{
		.ptr_g_Function = APP_rotate,
		.period = ROTATE_PERIOD
	}
};

// Pin configuration for the PWM signal
st_pinConfig st_g_pwmSignalPin = {PORTA_INDEX, DIO_PIN4, DIO_DIRECTION_OUTPUT, DIO_HIGH, DIO_UNLOCK};

// Button configurations for the start and stop buttons
st_button st_g_startButton = {PORTD_INDEX, DIO_PIN1};
st_button st_g_stopButton = {PORTD_INDEX, DIO_PIN2};

// LED configurations for various status indicators
st_leds st_g_longSideLed = {PORTB_INDEX, DIO_PIN0};
st_leds st_g_shortSideLed = {PORTB_INDEX, DIO_PIN1};
st_leds st_g_stopLed = {PORTB_INDEX, DIO_PIN2};
st_leds st_g_rotateLed = {PORTB_INDEX, DIO_PIN3};

// Interrupt configuration for the start button (External Interrupt 1)
st_exti st_g_startInterrupt = {
	.en_a_mode = INTERRUPT_FALLING_EDGE,
	.en_a_source = INTERRUPT_EXTERNAL_INT1,
	.EXT_InterruptHandler = APP_systemStart,
};

// Interrupt configuration for the stop button (External Interrupt 0)
st_exti st_g_stopInterrupt = {
	.en_a_mode = INTERRUPT_FALLING_EDGE,
	.en_a_source = INTERRUPT_EXTERNAL_INT0,
	.EXT_InterruptHandler = APP_systemStop,
};
/********************** FUNCTIONS DEFINITIONS ***************************************/

void APP_overflowRoutine()
{
	static i8 i8_gs_overFlowCounter = 0;
	TIMER_preload(3035,TIMER_TM1); 
	if (en_g_carStatus == SYSTEM_ON)
	{
		i8_gs_overFlowCounter++;
		if(st_g_systemSequence[u8_g_sequenceNumber].period == i8_gs_overFlowCounter)
		{
			i8_gs_overFlowCounter=-1;
			u8_g_sequenceNumber = (u8_g_sequenceNumber + 1) % SEQUENCE_MAX_NUMBER;
			u8_g_halfSecondStop = 1;
		}
		else
		{
			u8_g_halfSecondStop = 0;
		}
	}
	else if(en_g_carStatus == START_PRESSED)
	{
		i8_gs_overFlowCounter=-1;
		en_g_carStatus = SYSTEM_ON;
	}
}
/*************************************************************************************/
/**
 * @brief Timer0 overflow routine for generating PWM signals.
 *
 * This function is called when Timer0 overflows to generate PWM signals.
 * It toggles the PWM signal output between high and low states based on the duty cycle.
 * The duty cycle determines the ratio of time the signal is high to the total period.
 * 
 * @note This function assumes Timer0 is configured appropriately for PWM generation.
 */
void APP_pwmRoutine()
{
	static u8 u8_a_flag = 0;			// Static flag to keep track of the PWM signal state
	// Check the current state of the PWM signal
	if(u8_a_flag == 0){
		// If the signal is currently low, set it to high and update Timer0 preload value
		DIO_setPinStatus(&st_g_pwmSignalPin, DIO_HIGH);
		TIMER_preload(255 - u8_g_pwmDutyCycle,TIMER_TM0);
		u8_a_flag = 1;
		} else if(u8_a_flag == 1){
		// If the signal is currently high, set it to low and update Timer0 preload value
		DIO_setPinStatus(&st_g_pwmSignalPin, DIO_LOW);
		TIMER_preload(u8_g_pwmDutyCycle,TIMER_TM0);
		u8_a_flag = 0;
	}
		
}


/**
 * @brief Initialize the application.
 *
 * This function initializes various components and peripherals used in the application, including
 * pins, buttons, LEDs, interrupts, timers, and the motor driver.
 *
 * @return en_appErrorStatus representing the success or failure of the initialization.
 *         - APP_OK: Initialization successful.
 *         - APP_NOK: Initialization failed.
 */
en_appErrorStatus APP_init()
{
	en_appErrorStatus en_a_appErrorStatus = APP_OK;

	// Set the direction of the PWM signal pin
	en_a_appErrorStatus |= DIO_setPinDirection(&st_g_pwmSignalPin);

	// Initialize and connect the start and stop buttons
	en_a_appErrorStatus |= BUTTON_init(&st_g_startButton);
	en_a_appErrorStatus |= BUTTON_init(&st_g_stopButton);
	en_a_appErrorStatus |= BUTTON_connectIPU(&st_g_startButton);
	en_a_appErrorStatus |= BUTTON_connectIPU(&st_g_stopButton);

	// Initialize the LEDs
	en_a_appErrorStatus |= LED_init(&st_g_longSideLed);
	en_a_appErrorStatus |= LED_init(&st_g_shortSideLed);
	en_a_appErrorStatus |= LED_init(&st_g_rotateLed);
	en_a_appErrorStatus |= LED_init(&st_g_stopLed);

	// Initialize and configure external interrupts for start and stop buttons
	en_a_appErrorStatus |= EXTI_interruptInit(&st_g_startInterrupt);
	en_a_appErrorStatus |= EXTI_interruptInit(&st_g_stopInterrupt);

	// Initialize and configure timers
	en_a_appErrorStatus |= TIMER_init();
	en_a_appErrorStatus |= TIMER_setCallBack(TIMER0_OVF, APP_pwmRoutine);
	en_a_appErrorStatus |= TIMER_setCallBack(TIMER1_OVF, APP_overflowRoutine);
	en_a_appErrorStatus |= TIMER_preload(231, TIMER_TM0);

	// Enable global interrupts
	en_a_appErrorStatus |= GIE_enableGeneralInterrupt();

	// Initialize the motor driver
	en_a_appErrorStatus |= MOTOR_driverInitialize();

	return en_a_appErrorStatus;
}

/**
 * @brief External interrupt routine for handling the start button press event.
 *
 * This function is called when the start button is pressed. It initializes an LED on PORTC
 * and turns it on to indicate that the start button has been pressed. If the system is currently
 * in the OFF state, it starts Timer0 and Timer1, sets the system status to START_PRESSED, and
 * resumes Timer1 with the last recorded value. If the system is already in the ON state, it does nothing.
 */
void APP_systemStart()
{
    // Create an LED object for indication
    st_leds led = {PORTC_INDEX, DIO_PIN0};
    LED_init(&led);

    // Turn on the LED to indicate the start button press
    LED_on(&led);

    // Check if the system is currently OFF
    if (en_g_carStatus == SYSTEM_OFF)
    {
        // Start Timer0 and Timer1
        TIMER_start(TIMER_TM0);
        TIMER_start(TIMER_TM1);

        // Set the system status to START_PRESSED
        en_g_carStatus = START_PRESSED;

        // Resume Timer1 with the last recorded value
        TIMER_preload(TIMER_TM1, u16_g_timerLastValue);
    }
    // If the system is already ON, do nothing
}

/**
 * @brief External interrupt routine for handling the stop button press event.
 *
 * This function is called when the stop button is pressed. It reads the last recorded value of Timer1,
 * stops both Timer0 and Timer1, stops the car's motor direction, sets the system status to SYSTEM_OFF,
 * and updates the LED to indicate the stop state.
 */
void APP_systemStop()
{
    en_appErrorStatus en_a_appErrorStatus = APP_OK;

    // Read the last recorded value of Timer1
    TIMER_read(TIMER_TM1, &u16_g_timerLastValue);

    // Stop both Timer0 and Timer1
    TIMER_stop(TIMER_TM0);
    TIMER_stop(TIMER_TM1);

    // Stop the car's motor direction
    MOTOR_stopMotorDirection();

    // Set the system status to SYSTEM_OFF
    en_g_carStatus = SYSTEM_OFF;

    // Turn off the currently active LED (if any) and set it to indicate the stop state
    en_a_appErrorStatus |= LED_off(st_g_currentLed);
    st_g_currentLed = &st_g_stopLed;
    en_a_appErrorStatus |= LED_on(st_g_currentLed);
}


/**
 * @brief Function to handle the movement along the longest side of the rectangle.
 *
 * This function is responsible for controlling the robot's movement along the longest side
 * of the rectangle. It sets the PWM duty cycle to a default value of 128 (for straight movement),
 * turns off the currently active LED (if any), sets the current LED to indicate movement along
 * the longest side, and configures the left and right motors for forward direction.
 *
 * @return en_appErrorStatus representing the success or failure of the operation.
 *         - APP_OK: Operation successful.
 *         - APP_NOK: Operation failed.
 */
en_appErrorStatus APP_longestSide()
{
    u8_g_pwmDutyCycle = 128; // Set the PWM duty cycle to default
    en_appErrorStatus en_a_appErrorStatus = APP_OK;

    // Turn off the currently active LED (if any)
    en_a_appErrorStatus |= LED_off(st_g_currentLed);

    // Set the current LED to indicate movement along the longest side
    st_g_currentLed = &st_g_longSideLed;
    en_a_appErrorStatus |= LED_on(st_g_currentLed);

    // Configure the left and right motors for forward direction
    en_a_appErrorStatus |= MOTOR_leftMotorForwardDirection();
    en_a_appErrorStatus |= MOTOR_rightMotorForwardDirection();

    return en_a_appErrorStatus;
}

/**
 * @brief Function to handle the movement along the shortest side of the rectangle.
 *
 * This function is responsible for controlling the robot's movement along the shortest side
 * of the rectangle. It sets the PWM duty cycle to a value of 77 (for shorter movement),
 * turns off the currently active LED (if any), sets the current LED to indicate movement along
 * the shortest side, and configures the left and right motors for forward direction.
 *
 * @return en_appErrorStatus representing the success or failure of the operation.
 *         - APP_OK: Operation successful.
 *         - APP_NOK: Operation failed.
 */
en_appErrorStatus APP_shortestSide()
{
    u8_g_pwmDutyCycle = 77; // Set the PWM duty cycle for shorter movement
    en_appErrorStatus en_a_appErrorStatus = APP_OK;

    // Turn off the currently active LED (if any)
    en_a_appErrorStatus |= LED_off(st_g_currentLed);

    // Set the current LED to indicate movement along the shortest side
    st_g_currentLed = &st_g_shortSideLed;
    en_a_appErrorStatus |= LED_on(st_g_currentLed);

    // Configure the left and right motors for forward direction
    en_a_appErrorStatus |= MOTOR_leftMotorForwardDirection();
    en_a_appErrorStatus |= MOTOR_rightMotorForwardDirection();

    return en_a_appErrorStatus;
}

/**
 * @brief Function to handle the rotation of the robot.
 *
 * This function is responsible for controlling the robot's rotation. It turns off the currently
 * active LED (if any), sets the current LED to indicate rotation, and configures the motors for
 * the required rotation direction (left motor backward and right motor forward).
 *
 * @return en_appErrorStatus representing the success or failure of the operation.
 *         - APP_OK: Operation successful.
 *         - APP_NOK: Operation failed.
 */
en_appErrorStatus APP_rotate()
{
    en_appErrorStatus en_a_appErrorStatus = APP_OK;

    // Turn off the currently active LED (if any)
    en_a_appErrorStatus |= LED_off(st_g_currentLed);

    // Set the current LED to indicate rotation
    st_g_currentLed = &st_g_rotateLed;
    en_a_appErrorStatus |= LED_on(st_g_currentLed);

    // Configure the motors for rotation (left motor backward and right motor forward)
    en_a_appErrorStatus |= MOTOR_leftMotorBackwardDirection();
    en_a_appErrorStatus |= MOTOR_rightMotorForwardDirection();

    return en_a_appErrorStatus;
}
/**
 * @brief Function to temporarily stop the car for half a second.
 *
 * This function is responsible for temporarily stopping the car's movement for half a second.
 * It turns off the currently active LED (if any), sets the current LED to indicate the stop state,
 * and stops the car's motor direction.
 *
 * @return en_appErrorStatus representing the success or failure of the operation.
 *         - APP_OK: Operation successful.
 *         - APP_NOK: Operation failed.
 */
en_appErrorStatus APP_temporaryStop()
{
    en_appErrorStatus en_a_appErrorStatus = APP_OK;

    // Turn off the currently active LED (if any)
    en_a_appErrorStatus |= LED_off(st_g_currentLed);

    // Set the current LED to indicate the stop state
    st_g_currentLed = &st_g_stopLed;
    en_a_appErrorStatus |= LED_on(st_g_currentLed);

    // Stop the car's motor direction
    en_a_appErrorStatus |= MOTOR_stopMotorDirection();

    return en_a_appErrorStatus;
}
