/* 
 * File:   hal_gpio.h
 * Author: El-Greatly
 * https://www.linkedin.com/in/el-greatly-systems-engineer/
 * Created on February 12, 2023 
 */

#ifndef BIT_MATH_H
#define	BIT_MATH_H


/* Section : Macro Declarations  */
#define BIT_MASK               0x01
/* Section : Macro Functions Declarations */
#define ACCESS_ADDRESS(_ADDRESS)              (*(volatile u8 *)(_ADDRESS))

#define SET_BIT(REG,BIT_POSITION)                  ((REG) |=  ((BIT_MASK) << (BIT_POSITION) ));
#define CLEAR_BIT(REG,BIT_POSITION)             ((REG) &= ~((BIT_MASK) << (BIT_POSITION) ))
#define TOGGLE_BIT(REG,BIT_POSITION)          ((REG) ^=  ((BIT_MASK) << (BIT_POSITION) ))
#define GET_BIT(REG,BIT_POSITION)                 (((REG) >> (BIT_POSITION) & (BIT_MASK) ))
#define CLR_BIT(REG,BIT_POSITION)                 ((REG) &= ~((BIT_MASK) << (BIT_POSITION) ))


#endif 
