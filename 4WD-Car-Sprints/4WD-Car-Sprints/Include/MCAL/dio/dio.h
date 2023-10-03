/*
 * dio.h
 *
 * Created: 10/3/2023 2:17:42 PM
 *  Author: Mansour and El-Greatly
 */ 


#ifndef DIO_H_
#define DIO_H_

 /* Section : DIO_REG */

#define   DIO_PORTA                                (*(volatile u8 *)(0x3B)) 
#define   DIO_DDRA                                 (*(volatile u8 *)(0x3A)) 
#define   DIO_PINA                                   (*(volatile u8 *)(0x39))

#define   DIO_PORTB                                (*(volatile u8 *)(0x38)) 
#define   DIO_DDRB                                 (*(volatile u8 *)(0x37)) 
#define   DIO_PINB                                   (*(volatile u8 *)(0x36))

#define   DIO_PORTC                                (*(volatile u8 *)(0x35)) 
#define   DIO_DDRC                                 (*(volatile u8 *)(0x34)) 
#define   DIO_PINC                                   (*(volatile u8 *)(0x33))

#define   DIO_PORTD                                (*(volatile u8 *)(0x32)) 
#define   DIO_DDRD                                 (*(volatile u8 *)(0x31)) 
#define   DIO_PIND                                   (*(volatile u8 *)(0x30))


/* Section: Macro Declarations */

#define PORT_PIN_MAX_NUMBER  8
#define PORT_MAX_NUMBER      4

/* Section: Data Type Declarations */

typedef enum {
    DIO_LOW = 0,
    DIO_HIGH
}en_bitLogic;

typedef enum {
    DIO_DIRECTION_OUTPUT = 0,
    DIO_DIRECTION_INPUT
}en_pinDirection;


typedef enum {
    DIO_PIN0 = 0,
    DIO_PIN1,
    DIO_PIN2,
    DIO_PIN3,
    DIO_PIN4,
    DIO_PIN5,
    DIOO_PIN6,
    DIO_PIN7
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