#include "main.h"
#include "gpio.h"
#include "pwmConfig.h"

#define CALCULATE_PRESCALER(target_frequency, counter_period) HAL_RCC_GetHCLKFreq()/(counter_period * target_frequency)

static pwmConfig* pBuzzerConfiguration;
static TIM_HandleTypeDef* pPeriodTimer;

void vBuzzerInit(pwmConfig* pBuzzerConfig, TIM_HandleTypeDef* pPeriodTim, unsigned short int usFrequency, unsigned short int usPeriod){
    // Save configuration parameters
    pBuzzerConfiguration = pBuzzerConfig;
    pPeriodTimer = pPeriodTim;

    // Initialize the necessary timers
    HAL_TIM_PWM_Init(pBuzzerConfiguration->pTimeHandle);
    HAL_TIM_Base_Init(pPeriodTimer);

    // Calculate and set the correct pre-scale values for the timers as to implement the desired timer period and ring frequency
    // Since the default clock configuration is in the Mega Hertz, if we put the counter as 10^3, the resulting frequency will be 
    // in the order of thousands of hertz, which will make it easier to calculate the pre-scaler as to have a frequency of exactly 
    // (or as close as possible) 1000 Hz, and therefore a period of 1 ms, which is beneficial since the user input will be in ms.
    unsigned int uiCounter = 1000;
    unsigned int uiPreScaler = CALCULATE_PRESCALER(usFrequency, uiCounter);

    float fTargetTimerFrequency = 1.0 / ((float)usPeriod / 1000.0);
    unsigned int uiTimerCounter    = __HAL_TIM_CALC_PERIOD(HAL_RCC_GetHCLKFreq(), uiPreScaler, fTargetTimerFrequency);
    // unsigned int uiTimerPreScaler  = CALCULATE_PRESCALER((1/usPeriod), uiTimerCounter);

    __HAL_TIM_SET_AUTORELOAD(pBuzzerConfiguration->pTimeHandle, uiCounter);
    __HAL_TIM_SET_AUTORELOAD(pPeriodTimer, uiTimerCounter);

    __HAL_TIM_SET_COMPARE(pBuzzerConfiguration->pTimeHandle, pBuzzerConfiguration->uiChannel, uiCounter/10);


    __HAL_TIM_SET_PRESCALER(pBuzzerConfiguration->pTimeHandle, uiPreScaler);
    __HAL_TIM_SET_PRESCALER(pPeriodTimer, uiPreScaler);

    
}

void vBuzzerPlay(void){
	// pPeriodTimer->Instance->CNT = 1;
    HAL_TIM_PWM_Start(pBuzzerConfiguration->pTimeHandle, pBuzzerConfiguration->uiChannel);
    HAL_TIM_Base_Start_IT(pPeriodTimer);
}

void vBuzzerStop(void){
    __HAL_TIM_SET_COMPARE(pBuzzerConfiguration->pTimeHandle, pBuzzerConfiguration->uiChannel, 0); // Turn PWM Generation Off
    HAL_TIM_Base_Stop_IT(pPeriodTimer);                                                              // Stop ON-Timer count
}
