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

#include "buzzer.h"
#include "pwmConfig.h"
#include "application.h"
#include "buttonsEvents.h"
#include "heaterAndCooler.h"

// Application Specific Macros 
#define PWM_DUTYCYCLE_INCREMENT(x, delta) x+delta > 1 ? 1 : x+delta
#define PWM_DUTYCYCLE_DECREMENT(x, delta) x-delta < 0 ? 0 : x-delta

// Application Test Variables
float fCoolerDutyCycle = 0;
float fHeaterDutyCycle = 0;

// Config Settings 
pwmConfig xHeaterConfig = {&htim1, TIM_CHANNEL_1};
pwmConfig xCoolerConfig = {&htim8, TIM_CHANNEL_1};
pwmConfig xBuzzerConfig = {&htim20,TIM_CHANNEL_1};

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

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

    vButtonsEventsGpioCallback(GPIO_Pin);

}

void vApplicationButtonPressed(Button xPressedButton){
	if (xPressedButton == UP)
		fCoolerDutyCycle = PWM_DUTYCYCLE_INCREMENT(fCoolerDutyCycle, 0.1);

	else if (xPressedButton == DOWN)
		fCoolerDutyCycle = PWM_DUTYCYCLE_DECREMENT(fCoolerDutyCycle, 0.1);

	else if (xPressedButton == RIGHT)
		fHeaterDutyCycle = PWM_DUTYCYCLE_INCREMENT(fHeaterDutyCycle, 0.1);

	else if (xPressedButton == LEFT)
		fHeaterDutyCycle = PWM_DUTYCYCLE_DECREMENT(fHeaterDutyCycle, 0.1);


	vHeaterSetPwmDuty(fHeaterDutyCycle);
	vCoolerFanSetPwmDuty(fCoolerDutyCycle);
}

void vApplicationButtonReleased(Button xPressedButton){}

void vApplicationButtonThreeSecondPressed(Button xPressedButton){}

void vApplicationButtonHalfSecondPressed(Button xPressedButton){

	if (xPressedButton == UP)
		fCoolerDutyCycle = PWM_DUTYCYCLE_INCREMENT(fCoolerDutyCycle, 0.2);

	else if (xPressedButton == DOWN)
		fCoolerDutyCycle = PWM_DUTYCYCLE_DECREMENT(fCoolerDutyCycle, 0.2);

	else if (xPressedButton == RIGHT)
		fHeaterDutyCycle = PWM_DUTYCYCLE_INCREMENT(fHeaterDutyCycle, 0.2);

	else if (xPressedButton == LEFT)
		fHeaterDutyCycle = PWM_DUTYCYCLE_DECREMENT(fHeaterDutyCycle, 0.2);

	vHeaterSetPwmDuty(fHeaterDutyCycle);
	vCoolerFanSetPwmDuty(fCoolerDutyCycle);
}

void vApplicationStart() {

	heaterAndCoolerInit(&xHeaterConfig, &xCoolerConfig);
	vHeaterStart();
	vCoolerStart();

	vBuzzerInit(&xBuzzerConfig, &htim5, 1000, 5000);
	vButtonsEventsInit(&xBoardButtons, &htim7, &htim16, &vApplicationButtonPressed, &vApplicationButtonReleased, &vApplicationButtonHalfSecondPressed, &vApplicationButtonThreeSecondPressed);

	vBuzzerPlay();


    while (1) {

    }
}
