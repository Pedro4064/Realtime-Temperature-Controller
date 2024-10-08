 // **********************************************//
// File name:        buzzer.c                    //
// File description: This file implements the    //
//                   drivers for the buzzers.    //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 21/Jun/2024                 //
// Revision date:    21/Jun/2024                 //
// **********************************************//



#include "main.h"
#include "gpio.h"
#include "pwmConfig.h"
#include "stm32g474xx.h"

#define CALCULATE_PRESCALER(target_frequency, counter_period) HAL_RCC_GetHCLKFreq()/(counter_period * target_frequency)
#define PUSH_TIM_CONFIGS(tim) tim->Instance->EGR = TIM_EGR_UG; tim->Instance->SR = 0

static pwmConfig* pBuzzerConfiguration;
static TIM_HandleTypeDef* pPeriodTimer;
static unsigned int uiCompareValue;

void vBuzzerInit(pwmConfig* pBuzzerConfig, TIM_HandleTypeDef* pPeriodTim){
    // Save configuration parameters
    pBuzzerConfiguration = pBuzzerConfig;
    pPeriodTimer = pPeriodTim;

    // Initialize the necessary timers
    HAL_TIM_PWM_Init(pBuzzerConfiguration->pTimeHandle);
    HAL_TIM_Base_Init(pPeriodTimer);
}

void vBuzzerConfig(unsigned short int usFrequency, unsigned short int usPeriod){

    // From the function's input, calculate the necessary pre-scaler values and compare value for the pwm signal, 
    // keeping fixed the auto-reload counter value
    unsigned int uiCounter = 10000;
    float fTargetTimerFrequency = 1.0 / ((float)usPeriod / 1000.0);

    unsigned int uiPwmPreScaler   = CALCULATE_PRESCALER(usFrequency, uiCounter);
    unsigned int uiTimerPreScaler = CALCULATE_PRESCALER(fTargetTimerFrequency, uiCounter);

    // After calculating the values, it is necessary to assign the values to the correct timers, 
    // it is important to point out, however, that the updates normally are only applied after the 
    // first full cycle of each timer, but in our case it would call an interrupt based on the 
    // default timer configuration period, which we do not want. 
    // To avoid that, we force reset the timer peripherals in use (which rises an RS flag indicating)
    // an interrupt, so we also clear such RS flag, therefore "pushing" the updates to the peripherals
    // and avoiding the premature interrupt.
    __HAL_TIM_SET_AUTORELOAD(pBuzzerConfiguration->pTimeHandle, uiCounter);
    __HAL_TIM_SET_AUTORELOAD(pPeriodTimer, uiCounter);

    uiCompareValue = uiCounter/10;
    __HAL_TIM_SET_COMPARE(pBuzzerConfiguration->pTimeHandle, pBuzzerConfiguration->uiChannel, uiCompareValue);


    __HAL_TIM_SET_PRESCALER(pBuzzerConfiguration->pTimeHandle, uiPwmPreScaler);
    __HAL_TIM_SET_PRESCALER(pPeriodTimer, uiTimerPreScaler);

    PUSH_TIM_CONFIGS(pBuzzerConfiguration->pTimeHandle);
    PUSH_TIM_CONFIGS(pPeriodTimer);

}

void vBuzzerPlay(void){
    // Set the compare value to make sure it is started even after BuzzerStop
    __HAL_TIM_SET_COMPARE(pBuzzerConfiguration->pTimeHandle, pBuzzerConfiguration->uiChannel, uiCompareValue);
    HAL_TIM_PWM_Start(pBuzzerConfiguration->pTimeHandle, pBuzzerConfiguration->uiChannel);
    HAL_TIM_Base_Start_IT(pPeriodTimer);
}

void vBuzzerStop(void){
    __HAL_TIM_SET_COMPARE(pBuzzerConfiguration->pTimeHandle, pBuzzerConfiguration->uiChannel, 0); // Turn PWM Generation Off
    HAL_TIM_Base_Stop_IT(pPeriodTimer);                                                              // Stop ON-Timer count
}
