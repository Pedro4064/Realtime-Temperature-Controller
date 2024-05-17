#include "main.h"

#ifndef INC_H_TACHOMETER__
#define INC_H_TACHOMETER__

extern float fTachometerMeasuredSpeed;

void vTachometerInit(TIM_HandleTypeDef* pEnableTim, TIM_HandleTypeDef* pCounterTim, unsigned int uiEnablePeriod);

void vTachometerStartReadings(void);

void vTachometerUpdateSpeed(void);
#endif