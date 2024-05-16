#include "main.h"
#include "gpio.h"
#include "pwmConfig.h"

static pwmConfig* pHeaterConfiguration;
static pwmConfig* pCoolerConfiguration;

void heaterAndCoolerInit(pwmConfig* pHeaterConfig, pwmConfig* pCoolerConfig){

    pHeaterConfiguration = pHeaterConfig;
    pCoolerConfiguration = pCoolerConfig;

    HAL_TIM_PWM_Init(pHeaterConfiguration->pTimeHandle);
    HAL_TIM_PWM_Init(pCoolerConfiguration->pTimeHandle);
}

void vCoolerFanSetPwmDuty(float fCoolerPWM){
    __HAL_TIM_SET_COMPARE(pCoolerConfiguration->pTimeHandle, pCoolerConfiguration->uiChannel, fCoolerPWM*10000);
}

void vHeaterSetPwmDuty(float fHeaterPWM){
    __HAL_TIM_SET_COMPARE(pHeaterConfiguration->pTimeHandle, pHeaterConfiguration->uiChannel, fHeaterPWM*10000);
}

void vCoolerStart(void){
    HAL_TIM_PWM_Start(pCoolerConfiguration->pTimeHandle, pCoolerConfiguration->uiChannel);
}

void vHeaterStart(void){
    HAL_TIM_PWM_Start(pHeaterConfiguration->pTimeHandle, pHeaterConfiguration->uiChannel);
}

void vCoolerStop(void){
    HAL_TIM_PWM_Stop(pCoolerConfiguration->pTimeHandle, pCoolerConfiguration->uiChannel);
}

void vHeaterStop(void){
    HAL_TIM_PWM_Stop(pHeaterConfiguration->pTimeHandle, pHeaterConfiguration->uiChannel);
}