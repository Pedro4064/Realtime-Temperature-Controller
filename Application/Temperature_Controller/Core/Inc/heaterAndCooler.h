#ifndef INC_HEATER_AND_COOLER_H__
#define INC_HEATER_AND_COOLER_H__

#include "main.h"
#include "pwmConfig.h"

void heaterAndCoolerInit(pwmConfig* pHeaterConfig, pwmConfig* pCoolerConfig);

void vCoolerFanSetPwmDuty(float fCoolerPWM);

void vHeaterSetPwmDuty(float fHeaterPWM);

void vCoolerStart(void);

void vHeaterStart(void);

void vCoolerStop(void);

void vHeaterStop(void);

#endif