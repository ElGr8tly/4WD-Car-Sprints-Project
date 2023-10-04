/*
 * app.h
 *
 * Created: 10/4/2023 10:33:37 AM
 *  Author: mohamed mansour
 */ 


#ifndef APP_H_
#define APP_H_

#define SYSTEM_SEQ  3

#define SHORTEST_SIDE_PERIOD 4
#define LONGEST_SIDE_PERIOD 6
#define ROTATE_PERIOD 6


typedef struct
{
	void (*ptrFunction)(void);
	u8 period;
}car_mode;


void APP_systemStart();
void APP_longestSide();
void APP_shortestSide();
void APP_rotate();
void APP_stop();
void APP_systemStop();


#endif /* APP_H_ */