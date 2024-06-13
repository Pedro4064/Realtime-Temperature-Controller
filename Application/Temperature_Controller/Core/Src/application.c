// **********************************************//
// File name:        aplication.c                //
// File description: This file implements the    //
//                   temperature controller      //
//                   aplication layer.           //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 29/Mar/2024                 //
// Revision date:    29/Mar/2024                 //
// **********************************************//

#include <main.h>
#include <usart.h>
#include <tim.h>
#include <adc.h>
#include <i2c.h>

#include "lcd.h"
#include "pid.h"
#include "parser.h"
#include "buzzer.h"
#include "pwmConfig.h"
#include "tachometer.h"
#include "application.h"
#include "heaterAndCooler.h"
#include "temperatureSensor.h"
#include "applicationButtons.h"

// Application Specific Macros 
#define PWM_DUTYCYCLE_INCREMENT(x, delta) x+delta > 1 ? 1 : x+delta
#define PWM_DUTYCYCLE_DECREMENT(x, delta) x-delta < 0 ? 0 : x-delta
#define NEXT_SCREEN(x) x+1 > 2 ? 0 : x+1

// Application Timers Traceability 
#define BTN_DEBOUNCE_TIMER htim7
#define BTN_PRESS_TIMER htim16

#define TAC_ENABLE_TIMER htim4
#define TAC_PULSE_COUNTER_TIMER htim3

#define TMC_UPDATE_TIMER htim2

// Application Test Variables
float fCoolerDutyCycle = 0;
float fHeaterDutyCycle = 0;
float fRawTempVoltage  = 0;

applicationParameters xApplicationParameters;
unsigned short usPidWindUp = 1500;
float fActuatorSaturation = 3.3;
float fKp = 0.18;
float fKi = 2.34;
float fKd = 0.05;

unsigned char ucUartTemperatureMessage[11];

unsigned char ucScreen = 0;
unsigned char ucLcdTemperatureMessage[11];
unsigned char ucLcdTemperatureTargetMessage[11];
unsigned char ucLcdDutyCycleMessage[11];
unsigned char ucLcdKiMessage[11];
unsigned char ucLcdKpMessage[11];
unsigned char ucLcdKdMessage[11];
unsigned char ucTestStart = 1;

// Config Settings 
pwmConfig xHeaterConfig = {&htim1, TIM_CHANNEL_1};
pwmConfig xCoolerConfig = {&htim8, TIM_CHANNEL_1};
pwmConfig xBuzzerConfig = {&htim20,TIM_CHANNEL_1};
LcdConfig pLcdConfiguration = {&hi2c1, 0x27};

ButtonMapping xBoardButtons[] = {
                                        {BTN_UP_GPIO_Port,    BTN_UP_EXTI_IRQn, BTN_UP_Pin},
                                        {BTN_DOWN_GPIO_Port,  BTN_DOWN_EXTI_IRQn, BTN_DOWN_Pin},
                                        {BTN_LEFT_GPIO_Port,  BTN_LEFT_EXTI_IRQn, BTN_LEFT_Pin},
                                        {BTN_RIGHT_GPIO_Port, BTN_RIGHT_EXTI_IRQn, BTN_RIGHT_Pin},
                                        {BTN_ENTER_GPIO_Port, BTN_ENTER_EXTI_IRQn, BTN_ENTER_Pin}
                                    };


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* pTimer){

	if(pTimer->Instance == TIM7 || pTimer->Instance == TIM16)
		vButtonsEventsTimerCallback(pTimer);

	else if(pTimer->Instance == TIM5)
		vBuzzerStop();

	else if(pTimer->Instance == TIM4)
		vTachometerUpdateSpeed();

	else if(pTimer->Instance == TIM2){
		fRawTempVoltage = fTemperatureSensorGetCurrentTemperature();

		// Update Actuator Effort
		if (ucTestStart){
			float fTargetVoltage = fPidUpdateData(fRawTempVoltage, 50);
			fHeaterDutyCycle = fTargetVoltage/fActuatorSaturation;
			vHeaterSetPwmDuty(fHeaterDutyCycle);
		}

		// Format the string and send the data via UART 
		vParserFloatToString(&ucUartTemperatureMessage, fRawTempVoltage);
		HAL_UART_Transmit_IT(&hlpuart1, &ucUartTemperatureMessage, 11);

		// Format the string to be shown on the LCD display, but remove the last two elements (\n and \r) that are only needed for the UART string
		vParserFloatToString(&ucLcdTemperatureMessage, fRawTempVoltage);
		ucLcdTemperatureMessage[8] = '\0';
		ucLcdTemperatureMessage[9] = '\0';

	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

    vButtonsEventsGpioCallback(GPIO_Pin);

}


void vApplicationStart() {

	heaterAndCoolerInit(&xHeaterConfig, &xCoolerConfig);
	vHeaterStart();
	vCoolerStart();

	vApplicationButtonsInit(&xBoardButtons, &BTN_DEBOUNCE_TIMER, &BTN_PRESS_TIMER, &xApplicationParameters);

	vTachometerInit(&TAC_ENABLE_TIMER, &TAC_PULSE_COUNTER_TIMER, 500);
	vTachometerStartReadings();


	vTemperatureSensorInit(&hadc1);
	vPidInit(fKp, fKi, fKd, usPidWindUp, fActuatorSaturation);


	vLcdInitLcd(&pLcdConfiguration);
	vLcdBacklightON();

	HAL_TIM_Base_Init(&TMC_UPDATE_TIMER);
	HAL_TIM_Base_Start_IT(&TMC_UPDATE_TIMER);


    while (1) {
    }
}
