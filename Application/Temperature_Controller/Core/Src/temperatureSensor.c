#include "main.h"
#include "adc.h"

#define CONVERSION_RATE (10.0/1000.0)
#define MAX_ADC_VALUE (4096)
#define MAX_TEMP_VALUE 150
#define ADC_VREF 3.25

ADC_HandleTypeDef* pAdcPeripheral;
unsigned int uiRawTempVoltage;

void vTemperatureSensorInit(ADC_HandleTypeDef* pHadc){
    pAdcPeripheral = pHadc;

    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc1, &uiRawTempVoltage, 1);

}

float fTemperatureSensorGetCurrentTemperature(void){
    float fCurrentVoltage = uiRawTempVoltage * ADC_VREF / MAX_ADC_VALUE;
    float fCurrentTemperature = fCurrentVoltage / CONVERSION_RATE;

    return fCurrentTemperature;
}
