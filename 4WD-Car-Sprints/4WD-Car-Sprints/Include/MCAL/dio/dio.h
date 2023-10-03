/*
 * dio.h
 *
 * Created: 10/3/2023 2:17:42 PM
 *  Author: Mansour and El-Greatly
 */ 


#ifndef DIO_H_
#define DIO_H_

 /* Section : Includes */




/* Section: Macro Declarations */

#define PORT_PIN_MAX_NUMBER  8
#define PORT_MAX_NUMBER      4

/* Section: Data Type Declarations */

typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH
}en_bitLogic;

typedef enum {
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}en_pinDirection;


typedef enum {
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}en_pinIndex;

typedef enum {
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX
}en_portIndex;

typedef struct {
    u8 port : 2;      /* @ref port_index_t */
    u8 pin : 3;       /* @ref pin_index_t */
    u8 direction : 1; /* @ref direction_t */
    u8 logic : 1;     /* @ref logic_t */
}st_pinConfig;

/* Section: Function Declarations */
u8_returnType DIO_pinInit(const st_pinConfig *st_a_pinConfig);//greatly
u8_returnType DIO_setPinDirection(const st_pinConfig *st_a_pinConfig);//mansour
u8_returnType DIO_getPinDirection(const st_pinConfig *st_a_pinConfig, en_pinDirection *en_a_directionStatus);//greatly
u8_returnType DIO_setPinStatus( st_pinConfig *st_a_pinConfig, en_bitLogic en_a_bitLogic);//mansour
u8_returnType DIO_getPinStatus( st_pinConfig *st_a_pinConfig, en_bitLogic *en_a_bitLogic);//greatly
u8_returnType DIO_togglePinStatus( st_pinConfig *st_a_pinConfig);//mansour




#endif /* DIO_H_ */