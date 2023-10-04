/*
 * File:   hal_gpio.h
 * Author: El-Greatly
 * Created on February 12, 2023
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H

/* Section : Macro Declarations  */
#define NULL                ((void*)0)

typedef enum {
    LOGIC_LOW=0,
    LOGIC_HIGH
}en_standardLogic;

/* Section : Data Type Declarations */
typedef unsigned char           u8;

typedef unsigned short int      u16;

typedef unsigned long  int      u32;

typedef signed char             i8;

typedef signed short int        i16;

typedef signed long  int        i32;

typedef float                   f32;

typedef double					d64;

#endif	/* STD_TYPES_H */

