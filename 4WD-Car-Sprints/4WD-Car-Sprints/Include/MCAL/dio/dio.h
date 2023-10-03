/*
 * dio.h
 *
 * Created: 10/3/2023 2:17:42 PM
 *  Author: Mansour and El-Greatly
 */ 


#ifndef DIO_H_
#define DIO_H_

 /* Section : Includes */

 //#include "../pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"


/* Section: Macro Declarations */

#define PORT_PIN_MAX_NUMBER  8
#define PORT_MAX_NUMBER      4

/* Section: Data Type Declarations */

typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH
}EN_bitLogic;

typedef enum {
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}EN_pinDirection;


typedef enum {
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}EN_pinIndex;

typedef enum {
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX
}EN_portIndex;

typedef struct {
    u8 port : 2;      /* @ref port_index_t */
    u8 pin : 3;       /* @ref pin_index_t */
    u8 direction : 1; /* @ref direction_t */
    u8 logic : 1;     /* @ref logic_t */
}ST_pinConfig;

/* Section: Function Declarations */



#endif /* DIO_H_ */