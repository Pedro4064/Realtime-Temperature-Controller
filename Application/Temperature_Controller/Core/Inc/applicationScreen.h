#include "application.h"
#include "lcd.h"

#ifndef INC_APPLICATION_SCREEN_H_
#define INC_APPLICATION_SCREEN_H_

void vApplicationScreenInit(lcdConfig* pLcdConfiguration, applicationParameters* pAppParam);

void vApplicationScreenUpdate();

#endif