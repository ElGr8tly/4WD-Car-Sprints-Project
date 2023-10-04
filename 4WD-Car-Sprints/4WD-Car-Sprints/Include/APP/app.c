/*
 * app.c
 *
 * Created: 10/3/2023 2:11:11 PM
 *  Author: melgreatly
 */ 
#include "../LIB/STD_TYPES.h"
#include "app.h"


car_mode st_g_systemSequence[SYSTEM_SEQ] = {{APP_longestSide,6},{APP_rotate,2},{APP_shortestSide,4}};

void APP_systemStart()
{/*/*/
}
void APP_longestSide();
void APP_shortestSide();
void APP_rotate();
void APP_stop();
void APP_systemStop();