// **********************************************//
// File name:        temperatureSensor.h         //
// File description: This file defines           //
//                   the temp Sens. system       //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 21/Jun/2024                 //
// Revision date:    21/Jun/2024                 //
// **********************************************//



#include "adc.h"

#ifndef INC_H_TEMPERATURE_SENSOR__
#define INC_H_TEMPERATURE_SENSOR__

void vTemperatureSensorInit(ADC_HandleTypeDef* pHadc);

float fTemperatureSensorGetCurrentTemperature(void);

#endif