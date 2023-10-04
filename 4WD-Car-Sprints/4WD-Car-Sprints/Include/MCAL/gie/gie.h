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

u8_returnType GIE_enableGeneralInterrupt(void);

u8_returnType GIE_disableGeneralInterrupt(void);

#endif /* GIE_H_ */