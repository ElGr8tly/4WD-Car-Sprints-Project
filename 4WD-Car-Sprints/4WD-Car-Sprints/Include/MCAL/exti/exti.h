/*
 * exti.h
 *
 * Created: 10/3/2023 11:12:18 PM
 *  Author: msharfeldin
 */ 


#ifndef EXTI_H_
#define EXTI_H_




#define GICR        *((volatile u8 *)0x5B)
#define IVCE		0						//Interrupt Vector Select
#define IVSEL		1						//Interrupt Vector Change Enable
#define INTE2		5						//External Interrupt Request 2 Enable
#define INTE0		6						//External Interrupt Request 0 Enable
#define INTE1		7						//External Interrupt Request 1 Enable
#define GIFR        *((volatile u8 *)0x5A)
#define INTF2		5						//External Interrupt Flag 2
#define INTF0		6						//External Interrupt Flag 0
#define INTF1		7						//External Interrupt Flag 1
#define MCUCR       *((volatile u8 *)0x55)
#define ISC00		0                       // Interrupt Sense Control 0 bit 0
#define ISC01		1                       // Interrupt Sense Control 0 bit 1
#define ISC10		2						// Interrupt Sense Control 1 bit 0
#define ISC11		3						// Interrupt Sense Control 1 bit 1
#define MCUCSR      *((volatile u8 *)0x54)
#define ISC2		6                       //  Interrupt Sense Control 2

#define ENABLE				1
#define DISABLE				0



#define FALLING_EDGE_INT2	0
#define RISING_EDGE_INT2	1

void __vector_1(void) __attribute__ ((signal,used));
void __vector_2(void) __attribute__ ((signal,used));

/* This routine clears the interrupt enable for the external interrupt, INT0 */
#define EXT_INT0_InterruptDisable()         (CLEAR_BIT(GICR,INTE0))
/* This routine sets the interrupt enable for the external interrupt, INT0 */
#define EXT_INT0_InterruptEnable()          (SET_BIT(GICR,INTE0))
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT0_RisingEdgeSet()            do { \
													SET_BIT(MCUCR, ISC00); \
													SET_BIT(MCUCR, ISC01); \
											} while(0)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define  EXT_INT0_FallingEdgeSet()           do {\
												CLEAR_BIT(MCUCR, ISC00);\
												SET_BIT(MCUCR, ISC01); \
											} while(0)

#define EXT_INT0_LowLevelSet()				do { \
												CLEAR_BIT(MCUCR, ISC00); \
												CLEAR_BIT(MCUCR, ISC01); \
											} while(0)

#define EXT_INT0_LogicalChangeSet()       do { \
												SET_BIT(MCUCR, ISC00); \
												CLEAR_BIT(MCUCR, ISC01); \
											} while(0)


/* This routine clears the interrupt enable for the external interrupt, INT1 */
#define EXT_INT1_InterruptDisable()         (CLEAR_BIT(GICR,INTE1))
/* This routine sets the interrupt enable for the external interrupt, INT0 */
#define EXT_INT1_InterruptEnable()          (SET_BIT(GICR,INTE1))
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT1_RisingEdgeSet()            do { \
												SET_BIT(MCUCR, ISC10); \
												SET_BIT(MCUCR, ISC11); \
											} while(0)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT1_FallingEdgeSet()           do { \
												CLEAR_BIT(MCUCR, ISC10); \
												SET_BIT(MCUCR, ISC11); \
											} while(0)

#define EXT_INT1_LowLevelSet()				do { \
													CLEAR_BIT(MCUCR, ISC10); \
													CLEAR_BIT(MCUCR, ISC11); \
												} while(0)

#define EXT_INT1_LogicalChangeSet()       do { \
													SET_BIT(MCUCR, ISC10); \
													CLEAR_BIT(MCUCR, ISC11); \
												} while(0)

typedef void (*EXT_InterruptHandler)(void);

typedef enum{
	INTERRUPT_LOW_LEVEL = 0,
	INTERRUPT_LOGICAL_CHANGE   ,
	INTERRUPT_FALLING_EDGE ,
	INTERRUPT_RISING_EDGE
}interrupt_INTx_mode;

typedef enum{
	INTERRUPT_EXTERNAL_INT0 =  0,
	INTERRUPT_EXTERNAL_INT1,
	INTERRUPT_EXTERNAL_INT2
}interrupt_INTx_src;

typedef struct{
	void (* EXT_InterruptHandler)(void);
	interrupt_INTx_mode en_a_mode;
	interrupt_INTx_src en_a_source;
}interrupt_INTx_t;

typedef enum {
	EXTI_OK = 0,
	EXTI_NOK,
	EXTI_WRONG_DATA,
}en_extiErrorStatus;

en_extiErrorStatus EXTI_interruptInit(const interrupt_INTx_t *st_a_intObj);


en_extiErrorStatus EXTI_interruptDeInit(const interrupt_INTx_t *st_a_intObj);

#endif /* EXTI_H_ */