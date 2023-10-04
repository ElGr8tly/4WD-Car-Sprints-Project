/*
 * app.h
 *
 * Created: 10/4/2023 10:33:37 AM
 *  Author: mohamed mansour
 */ 


#ifndef APP_H_
#define APP_H_


#define SHORTEST_SIDE_PERIOD 4
#define LONGEST_SIDE_PERIOD 6
#define ROTATE_PERIOD 6

#define SEQUENCE_MAX_NUMBER	4



typedef struct
{
	void (*ptrFunction)(void);
	u8 period;
}car_mode;

typedef enum 
{
	SYSTEM_ON = 0;
	SYSTEM_OFF;
}en_system_status;

void APP_systemStart();
void APP_longestSide();
void APP_shortestSide();
void APP_rotate();
void APP_stop();
void APP_systemStop();
void APP_overflowRoutine();
void APP_pwmRoutine();

#endif /* APP_H_ */