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

#include <stm32g474xx.h>
#include <main.h>
#include <tim.h>

#include "application.h"
#include "matrixKeyboard.h" 
#include "buttonsEvents.h"
#include "led.h"

#define TEST_RUN 1

static MatrixKeyboard* pMatrixKeayboardStatus;
static int single_press_test = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* timer) {
    if (timer->Instance == TIM6)
        vMatrixKeyboardUpdateCallback();

    else if (timer->Instance == TIM7 || timer->Instance == TIM16)
        vButtonsEventsTimerCallback(timer);
    
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    vButtonsEventsGpioCallback(GPIO_Pin);

}

void vButtonsEventCallbackPressedEvent(Button pressedButton){
    single_press_test++;

}

void vButtonsEventCallbackReleasedEvent(Button pressedButton){

}

void vApplicationStart() {
    // Initialize LED Drivers
    LedMapping xBoardLeds[] = {
                                {GPIOA, LED_SOLID_GREEN_PIN},
                                {GPIOA, LED_SOLID_YELLOW_PIN},
                                {GPIOB, LED_DIM_RED_PIN},
                                {GPIOA, LED_DIM_GREEN_PIN},
                                {GPIOB, LED_DIM_BLUE_PIN}
                              };
    vLedInit(&xBoardLeds);

    // Initialize Button Drivers
    ButtonMapping xBoardButtons[] = {
                                        {BTN_UP_GPIO_Port,    BTN_UP_EXTI_IRQn, BTN_UP_Pin},
                                        {BTN_DOWN_GPIO_Port,  BTN_DOWN_EXTI_IRQn, BTN_DOWN_Pin},
                                        {BTN_LEFT_GPIO_Port,  BTN_LEFT_EXTI_IRQn, BTN_LEFT_Pin},
                                        {BTN_RIGHT_GPIO_Port, BTN_RIGHT_EXTI_IRQn, BTN_RIGHT_Pin},
                                        {BTN_ENTER_GPIO_Port, BTN_ENTER_EXTI_IRQn, BTN_ENTER_Pin}
                                    };
    vButtonsEventsInit(&xBoardButtons, &htim7, &htim16, &vButtonsEventCallbackPressedEvent, &vButtonsEventCallbackReleasedEvent);

    // Initialize Matrix Keyboard
    MatrixMapping xKeyboardMapping = {
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
    vMatrixKeyboardInit(xKeyboardMapping, &htim6);

    // Initialize Application
    while (1) {
    }
}
