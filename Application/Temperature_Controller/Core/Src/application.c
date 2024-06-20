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

#include "pid.h"
#include "parser.h"
#include "buzzer.h"
#include "pwmConfig.h"
#include "tachometer.h"
#include "application.h"
#include "matrixKeyboard.h"
#include "heaterAndCooler.h"
#include "applicationScreen.h"
#include "temperatureSensor.h"
#include "applicationButtons.h"
#include "communicationStateMachine.h"


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

#define BUZZER_PWM_TIMER htim5

// Application Test Variables
float fCoolerDutyCycle = 0;
float fHeaterDutyCycle = 0;
float fRawTempVoltage  = 0;

applicationParameters xApplicationParameters = {.tempMgtCtl.ucHeatingOn = 1,
												.tempMgtCtl.fTemperatureTarget = 40,
												.tempMgtCtl.fKp = 0.18,
												.tempMgtCtl.fKi = 2.34,
												.tempMgtCtl.fKd = 0.05,
												.buzzerInterface.usFrequency = 1000,
												.buzzerInterface.usPeriod = 500
												};
unsigned short usPidWindUp = 1500;
float fActuatorSaturation = 3.3;

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
lcdConfig xLcdConfiguration = {&hi2c1, 0x27};

ButtonMapping xBoardButtons[] = {
                                        {BTN_UP_GPIO_Port,    BTN_UP_EXTI_IRQn, BTN_UP_Pin},
                                        {BTN_DOWN_GPIO_Port,  BTN_DOWN_EXTI_IRQn, BTN_DOWN_Pin},
                                        {BTN_LEFT_GPIO_Port,  BTN_LEFT_EXTI_IRQn, BTN_LEFT_Pin},
                                        {BTN_RIGHT_GPIO_Port, BTN_RIGHT_EXTI_IRQn, BTN_RIGHT_Pin},
                                        {BTN_ENTER_GPIO_Port, BTN_ENTER_EXTI_IRQn, BTN_ENTER_Pin}
                                    };

MatrixMapping xKeyboardMapping ={
									rows : {
										{KEYBOARD_L1_GPIO_Port, KEYBOARD_L1_Pin},
										{KEYBOARD_L2_GPIO_Port, KEYBOARD_L2_Pin},
										{KEYBOARD_L3_GPIO_Port, KEYBOARD_L3_Pin},
										{KEYBOARD_L4_GPIO_Port, KEYBOARD_L4_Pin}},

									columns : {
										{KEYBOARD_C1_GPIO_Port, KEYBOARD_C1_Pin},
										{KEYBOARD_C2_GPIO_Port, KEYBOARD_C2_Pin},
										{KEYBOARD_C3_GPIO_Port, KEYBOARD_C3_Pin},
										{KEYBOARD_C4_GPIO_Port, KEYBOARD_C4_Pin}}

								};


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* pTimer){

	if (pTimer->Instance == TIM6)
        vMatrixKeyboardUpdateCallback();

	if(pTimer->Instance == TIM7 || pTimer->Instance == TIM16)
		vButtonsEventsTimerCallback(pTimer);

	else if(pTimer->Instance == TIM5)
		vBuzzerStop();

	else if(pTimer->Instance == TIM4)
		vTachometerUpdateSpeed();

	else if(pTimer->Instance == TIM2){
		xApplicationParameters.tempMgtCtl.fTemperatureCurrent = fTemperatureSensorGetCurrentTemperature();

		// Update Actuator Effort
		if (xApplicationParameters.tempMgtCtl.ucHeatingOn){
			float fTargetVoltage = fPidUpdateData(xApplicationParameters.tempMgtCtl.fTemperatureCurrent, xApplicationParameters.tempMgtCtl.fTemperatureTarget);
			 xApplicationParameters.tempMgtCtl.fDutyCycleHeater = fTargetVoltage/fActuatorSaturation;
			vHeaterSetPwmDuty(xApplicationParameters.tempMgtCtl.fDutyCycleHeater);
			vCoolerFanSetPwmDuty(0);
		}
		else{
			vHeaterSetPwmDuty(0);
			vCoolerFanSetPwmDuty(100);
		}

	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

    vButtonsEventsGpioCallback(GPIO_Pin);

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* pHUart){
    if (pHUart == &hlpuart1)
        vCommunicationStateMachineProcessByte();
}

void vApplicationStart() {

	heaterAndCoolerInit(&xHeaterConfig, &xCoolerConfig);
	vHeaterStart();
	vCoolerStart();

	vTachometerInit(&TAC_ENABLE_TIMER, &TAC_PULSE_COUNTER_TIMER, 500);
	vTachometerStartReadings();

	vTemperatureSensorInit(&hadc1);
	vPidInit(xApplicationParameters.tempMgtCtl.fKp, xApplicationParameters.tempMgtCtl.fKi, xApplicationParameters.tempMgtCtl.fKd, usPidWindUp, fActuatorSaturation);

	vApplicationButtonsInit(&xBoardButtons, &BTN_DEBOUNCE_TIMER, &BTN_PRESS_TIMER, &xApplicationParameters);
	vApplicationScreenInit(&xLcdConfiguration, &xApplicationParameters);

	vBuzzerInit(&xBuzzerConfig, &BUZZER_PWM_TIMER);
	vBuzzerConfig(xApplicationParameters.buzzerInterface.usFrequency, xApplicationParameters.buzzerInterface.usPeriod);


    vCommunicationStateMachineInit(&hlpuart1, &xApplicationParameters);

	HAL_TIM_Base_Init(&TMC_UPDATE_TIMER);
	HAL_TIM_Base_Start_IT(&TMC_UPDATE_TIMER);



    vMatrixKeyboardInit(xKeyboardMapping, &htim6, &xApplicationParameters.xKeyboardQueue);


    while (1) {
		xApplicationParameters.tempMgtCtl.uiVelocityCooler = fTachometerMeasuredSpeed;
    	vApplicationScreenUpdate();

		// Update PID values to any new values if changed by the applications interface (both local and UART)
		if(xApplicationParameters.tempMgtCtl.cPidConfigChanged){
			xApplicationParameters.tempMgtCtl.cPidConfigChanged = 0;
			vPidSetKp(xApplicationParameters.tempMgtCtl.fKp);
			vPidSetKi(xApplicationParameters.tempMgtCtl.fKi);
			vPidSetKd(xApplicationParameters.tempMgtCtl.fKd);
		}

		// If buzzer configurations changed, update the driver settings
		if(xApplicationParameters.buzzerInterface.cBuzzerConfigChanged){
			xApplicationParameters.buzzerInterface.cBuzzerConfigChanged = 0;
			vBuzzerConfig(xApplicationParameters.buzzerInterface.usFrequency, xApplicationParameters.buzzerInterface.usPeriod);
		}

		// Play the buzzer if any interface requests it
		if(xApplicationParameters.buzzerInterface.cPlay){
			vBuzzerPlay();
			xApplicationParameters.buzzerInterface.cPlay = 0;
		}
    }
}
