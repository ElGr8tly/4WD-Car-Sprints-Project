/*
 * dio.h
 *
 * Created: 10/3/2023 2:17:42 PM
 *  Author: Mansour and El-Greatly
 */ 

#ifndef DIO_H_
#define DIO_H_

 /* Section : DIO_REG */

#define   DIO_PORTA                                  (*(volatile u8 *)(0x3B)) 
#define   DIO_DDRA                                   (*(volatile u8 *)(0x3A)) 
#define   DIO_PINA                                   (*(volatile u8 *)(0x39))

#define   DIO_PORTB                                  (*(volatile u8 *)(0x38)) 
#define   DIO_DDRB                                   (*(volatile u8 *)(0x37)) 
#define   DIO_PINB                                   (*(volatile u8 *)(0x36))

#define   DIO_PORTC                                  (*(volatile u8 *)(0x35)) 
#define   DIO_DDRC                                   (*(volatile u8 *)(0x34)) 
#define   DIO_PINC                                   (*(volatile u8 *)(0x33))

#define   DIO_PORTD                                  (*(volatile u8 *)(0x32)) 
#define   DIO_DDRD                                   (*(volatile u8 *)(0x31)) 
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

typedef enum {
    DIO_OK = 0,
    DIO_NOK,
    DIO_WRONG_INPUT,
}en_dioErrorStatus;

typedef struct {
    u8 u8_g_port : 2;      /* @ref en_portIndex */
    u8 u8_g_pin : 3;       /* @ref en_pinIndex */
    u8 u8_g_direction : 1; /* @ref en_pinDirection */
    u8 u8_g_logic : 1;     /* @ref en_bitLogic */
    u8 u8_g_reserved : 1;  /* @ref Locked or Available  */
}st_pinConfig;

/* Section: Function Declarations */
en_dioErrorStatus DIO_pinInitialize(const st_pinConfig *st_a_pinConfig);
en_dioErrorStatus DIO_setPinDirection(const st_pinConfig *st_a_pinConfig);
en_dioErrorStatus DIO_getPinDirection( st_pinConfig *st_a_pinConfig, en_pinDirection *en_a_directionStatus);
en_dioErrorStatus DIO_setPinPullupResistor(const st_pinConfig* st_a_pinConfig);
en_dioErrorStatus DIO_disablePinPullupResistor(const st_pinConfig* st_a_pinConfig);
en_dioErrorStatus DIO_setPinStatus( st_pinConfig *st_a_pinConfig, en_bitLogic en_a_bitLogic);
en_dioErrorStatus DIO_getPinStatus( st_pinConfig *st_a_pinConfig, en_bitLogic *en_a_bitLogic);
en_dioErrorStatus DIO_togglePinStatus( st_pinConfig *st_a_pinConfig);
en_dioErrorStatus DIO_lockPin(st_pinConfig* st_a_pinConfig);
en_dioErrorStatus DIO_unlockPin(st_pinConfig* st_a_pinConfig);
#endif /* DIO_H_ */