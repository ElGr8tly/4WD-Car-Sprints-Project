/*
 * gie.h
 *
 * Created: 10/3/2023 11:12:00 PM
 *  Author: msharfeldin
 */ 


#ifndef GIE_H_
#define GIE_H_

#define SREG							*((volatile u8 *)0x5F)
#define GLOBAL_INTERRUPT_ENABLE_BIT		7

typedef enum {
	GIE_OK = 0,
	GIEO_NOK,
}en_gieErrorStatus;

en_gieErrorStatus GIE_enableGeneralInterrupt(void);

en_gieErrorStatus GIE_disableGeneralInterrupt(void);

#endif /* GIE_H_ */