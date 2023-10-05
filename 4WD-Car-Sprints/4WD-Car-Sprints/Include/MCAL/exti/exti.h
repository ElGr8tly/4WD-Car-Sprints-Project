/*
 * exti.h
 *
 * Created: 10/3/2023 11:12:18 PM
 *  Author: msharfeldin
 */ 



#ifndef EXTI_H_
#define EXTI_H_


/***************************************************/
/**            EXTERNAL INTERRUPT REGISTERS       **/
/***************************************************/

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

//ISR DECLARTIONS
void __vector_1(void) __attribute__ ((signal,used));
void __vector_2(void) __attribute__ ((signal,used));


/****************************** MACROS DEFINETION SECTION ****************************/

/* This routine clears the interrupt enable for the external interrupt, INT0 */
#define EXT_INT0_InterruptDisable()         (CLEAR_BIT(GICR,INTE0))
/* This routine sets the interrupt enable for the external interrupt, INT0 */
#define EXT_INT0_InterruptEnable()          (SET_BIT(GICR,INTE0))
/* This routine set the edge detect of the extern interrupt INT0 to negative edge */
#define EXT_INT0_RisingEdgeSet()            do { \
													SET_BIT(MCUCR, ISC00); \
													SET_BIT(MCUCR, ISC01); \
											} while(0)
/* This routine set the edge detect of the extern interrupt INT0 to positive edge */
#define  EXT_INT0_FallingEdgeSet()           do {\
												CLEAR_BIT(MCUCR, ISC00);\
												SET_BIT(MCUCR, ISC01); \
											} while(0)
/* This routine set the extern interrupt INT0 to low level */
#define EXT_INT0_LowLevelSet()				do { \
												CLEAR_BIT(MCUCR, ISC00); \
												CLEAR_BIT(MCUCR, ISC01); \
											} while(0)
/* This routine set the extern interrupt INT0 to any logical level change */
#define EXT_INT0_LogicalChangeSet()       do { \
												SET_BIT(MCUCR, ISC00); \
												CLEAR_BIT(MCUCR, ISC01); \
											} while(0)


/* This routine clears the interrupt enable for the external interrupt, INT1 */
#define EXT_INT1_InterruptDisable()         (CLEAR_BIT(GICR,INTE1))
/* This routine sets the interrupt enable for the external interrupt, INT1 */
#define EXT_INT1_InterruptEnable()          (SET_BIT(GICR,INTE1))
/* This routine set the edge detect of the extern interrupt INT1 to negative edge */
#define EXT_INT1_RisingEdgeSet()            do { \
												SET_BIT(MCUCR, ISC10); \
												SET_BIT(MCUCR, ISC11); \
											} while(0)
/* This routine set the edge detect of the extern interrupt INT1 to positive edge */
#define EXT_INT1_FallingEdgeSet()           do { \
												CLEAR_BIT(MCUCR, ISC10); \
												SET_BIT(MCUCR, ISC11); \
											} while(0)
/* This routine set the extern interrupt INT1 to low level */
#define EXT_INT1_LowLevelSet()				do { \
													CLEAR_BIT(MCUCR, ISC10); \
													CLEAR_BIT(MCUCR, ISC11); \
												} while(0)
/* This routine set the extern interrupt INT1 to any logical level change */
#define EXT_INT1_LogicalChangeSet()       do { \
													SET_BIT(MCUCR, ISC10); \
													CLEAR_BIT(MCUCR, ISC11); \
												} while(0)


/************************** USER DEFINED PROTOTYPES ************************/


//ENUM to describe the mode of the external interrupt
typedef enum{
	INTERRUPT_LOW_LEVEL = 0,
	INTERRUPT_LOGICAL_CHANGE   ,
	INTERRUPT_FALLING_EDGE ,
	INTERRUPT_RISING_EDGE
}interrupt_INTx_mode;

//ENUM to represent the source of the external interrupt
typedef enum{
	INTERRUPT_EXTERNAL_INT0 =  0,
	INTERRUPT_EXTERNAL_INT1,
	INTERRUPT_EXTERNAL_INT2
}interrupt_INTx_src;

//Structure to hold all data of  the external interrupt
typedef struct{
	void (* EXT_InterruptHandler)(void);
	interrupt_INTx_mode en_a_mode;
	interrupt_INTx_src en_a_source;
}interrupt_INTx_t;

//ENUM for errors of the module
typedef enum {
	EXTI_OK = 0,
	EXTI_NOK,
	EXTI_WRONG_DATA,
}en_extiErrorStatus;



/************************** FUNCTION DECLARATION ************************/

 /******************************************************************************/
 /* Function: EXTI_interruptInit    @written by: Mahmoud Sharf-Eldin           */
 /* I/P Parameters: interrupt_INTx_t										   */
 /* Returns: en_extiErrorStatus				                                   */
 /* Description: This Function initialize a given external interrupt           */
 /******************************************************************************/
  /* Options														           */
  /*****************************************************************************/
  /* mode     : FALLING_EDGE, RISING_EDGE, LOW_LEVEL, LOGICAL_CHANGE           */
  /* source   : INT0, INT1, INT2        						               */
  /*****************************************************************************/
  
en_extiErrorStatus EXTI_interruptInit(const interrupt_INTx_t *st_a_intObj);

  /******************************************************************************/
  /* Function: EXTI_interruptDeInit    @written by: Mahmoud Sharf-Eldin         */
  /* I/P Parameters: interrupt_INTx_t										    */
  /* Returns: en_extiErrorStatus				                                */
  /* Description: This Function de-initialize a given external interrupt        */
  /******************************************************************************/
  /* Options														            */
  /******************************************************************************/
  /* mode     : FALLING_EDGE, RISING_EDGE, LOW_LEVEL, LOGICAL_CHANGE            */
  /* source   : INT0, INT1, INT2        						                */
  /******************************************************************************/

en_extiErrorStatus EXTI_interruptDeInit(const interrupt_INTx_t *st_a_intObj);

#endif /* EXTI_H_ */