#include "main.h"
#include "stm32g474xx.h"


#define CALCULATE_PRESCALER(target_frequency, counter_period) HAL_RCC_GetHCLKFreq()/(counter_period * target_frequency)
#define PUSH_TIM_CONFIGS(tim) tim->Instance->EGR = TIM_EGR_UG; tim->Instance->SR = 0

TIM_HandleTypeDef* pEnableTimer;
TIM_HandleTypeDef* pCounterTimer;

float fTachometerMeasuredSpeed = 0;
unsigned int uiCountingPeriod = 0;

void vTachometerInit(TIM_HandleTypeDef* pEnableTim, TIM_HandleTypeDef* pCounterTim, unsigned int uiEnablePeriod){
    pEnableTimer = pEnableTim;
    pCounterTimer = pCounterTim;
    uiCountingPeriod = uiEnablePeriod;

    // Initialize the timers
    HAL_TIM_Base_Init(pEnableTimer);
    HAL_TIM_Base_Init(pCounterTimer);

    // Configure the enable timer
    unsigned int uiCounter = 10000;
    float fTargetTimerFrequency = 1.0 / ((float)uiEnablePeriod / 1000.0);

    unsigned int uiTimerPreScaler = CALCULATE_PRESCALER(fTargetTimerFrequency, uiCounter);
    __HAL_TIM_SET_AUTORELOAD(pEnableTimer, uiCounter);
    __HAL_TIM_SET_PRESCALER(pEnableTimer, uiTimerPreScaler);

    PUSH_TIM_CONFIGS(pEnableTimer);

}

void vTachometerStartReadings(void){
    HAL_TIM_Base_Start_IT(pEnableTimer);
    HAL_TIM_Base_Start(pCounterTimer);
}

void vTachometerUpdateSpeed(void){
    unsigned int uiNumberOfPulses = pCounterTimer->Instance->CNT;
    uiNumberOfPulses = uiNumberOfPulses / 9;                        // To get the number of pulses per fan blade
    fTachometerMeasuredSpeed = uiNumberOfPulses/uiCountingPeriod;   // To get the frequency just divide the number of pulses per blade by the period of measurement


    pCounterTimer->Instance->CNT = 0;                               // Reset the pulse counter to 0 to get new measurements
}