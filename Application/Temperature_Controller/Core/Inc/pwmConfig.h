#ifndef INC_PWM_CONFIG_H__
#define INC_PWM_CONFIG_H__

#include "main.h"

typedef struct PWM_CONFIG{
    TIM_HandleTypeDef* pTimeHandle;
    unsigned int uiChannel;
}pwmConfig;

#endif