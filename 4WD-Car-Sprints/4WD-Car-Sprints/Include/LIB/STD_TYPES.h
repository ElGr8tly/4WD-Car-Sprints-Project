/*
 * File:   hal_gpio.h
 * Author: El-Greatly
 * https://www.linkedin.com/in/el-greatly-systems-engineer/
 * Created on February 12, 2023
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H

/* Section : Macro Declarations  */
#define NULL                ((void*)0)

#define STD_OFF               0
#define STD_ON                1

#define STD_LOW              0
#define STD_HIGH             1

#define  E_OK              (STD_ReturnType)1
#define  E_NOK              (STD_ReturnType)0
/* Section : Data Type Declarations */
typedef unsigned char           u8;

typedef unsigned short int      u16;

typedef unsigned long  int      u32;

typedef signed char             i8;

typedef signed short int        i16;

typedef signed long  int        i32;

typedef  float                  f32;

typedef  double                 d64;

typedef u8                 STD_ReturnType;





#endif	/* STD_TYPES_H */

