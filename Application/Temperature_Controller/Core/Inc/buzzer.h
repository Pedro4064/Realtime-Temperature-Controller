#ifndef INC_BUZZER_H__
#define INC_BUZZER_H__

#include "main.h"
#include "gpio.h"
#include "pwmConfig.h"

void vBuzzerInit(pwmConfig* pBuzzerConfig, TIM_HandleTypeDef* pPeriodTim);

void vBuzzerConfig(unsigned short int usFrequency, unsigned short int usPeriod);

void vBuzzerPlay(void);

void vBuzzerStop(void);

#endif