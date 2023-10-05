/*
 * gie.h
 *
 * Created: 10/3/2023 11:12:00 PM
 *  Author: msharfeldin
 */ 



#ifndef GIE_H_
#define GIE_H_

/***************************************************/
/**            EXTERNAL INTERRUPT REGISTERS       **/
/***************************************************/

#define SREG							*((volatile u8 *)0x5F)
#define GLOBAL_INTERRUPT_ENABLE_BIT		7

/************************** USER DEFINETION PROTOTYPES ************************/
//ENUM for errors of the module
typedef enum {
	GIE_OK = 0,
	GIEO_NOK,
}en_gieErrorStatus;

/************************** FUNCTION DECLARATION ************************/

/******************************************************************************/
/* Function: GIE_enableGeneralInterrupt    @written by: Mahmoud Sharf-Eldin   */
/* Returns: en_gieErrorStatus				                                  */
/* Description: This Function enable global interrupts                        */
/******************************************************************************/

en_gieErrorStatus GIE_enableGeneralInterrupt(void);

/******************************************************************************/
/* Function: GIE_disableGeneralInterrupt    @written by: Mahmoud Sharf-Eldin  */
/* Returns: en_gieErrorStatus				                                  */
/* Description: This Function disable global interrupts                       */
/******************************************************************************/
en_gieErrorStatus GIE_disableGeneralInterrupt(void);

#endif /* GIE_H_ */