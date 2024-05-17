#include "adc.h"

#ifndef INC_H_TEMPERATURE_SENSOR__
#define INC_H_TEMPERATURE_SENSOR__

void vTemperatureSensorInit(ADC_HandleTypeDef* pHadc);

float fTemperatureSensorGetCurrentTemperature(void);

#endif