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
#include <usart.h>
#include <tim.h>

#include "application.h"
#include "matrixKeyboard.h" 
#include "buttonsEvents.h"
#include "communicationStateMachine.h"
#include "led.h"
#include "parser.h"

#define TEST_RUN 1
#define UART_BUFFER_SIZE 10

static MatrixKeyboard* pMatrixKeayboardStatus;
static int iBinaryCounter = 0;

SystemParameters xSystemParameters;



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* timer) {
    if (timer->Instance == TIM6)
        vMatrixKeyboardUpdateCallback();

    else if (timer->Instance == TIM7 || timer->Instance == TIM16)
        vButtonsEventsTimerCallback(timer);
    
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    vButtonsEventsGpioCallback(GPIO_Pin);

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* pHUart){
    if (pHUart == &hlpuart1)
        vCommunicationStateMachineProcessByte();
}

void vButtonsEventCallbackPressedEvent(Button pressedButton){

    #if TEST_RUN==1
        vLedToggle(DIM_BLUE);
        vLedToggle(DIM_GREEN);
        vLedToggle(DIM_RED);
        vLedToggle(SOLID_GREEN);
        vLedToggle(SOLID_YELLOW);
    #endif

    #if TEST_RUN==2
        if(pressedButton == UP)
            iBinaryCounter++;
        else if (pressedButton == DOWN)
            iBinaryCounter--;
    #endif
}

void vButtonsEventCallbackReleasedEvent(Button pressedButton){

}

void vButtonsEventHalfSecondEvent(Button pressedButton){
    #if TEST_RUN==2
        if(pressedButton == UP)
            iBinaryCounter++;
        else if (pressedButton == DOWN)
            iBinaryCounter--;
    #endif
}

void vButtonsEventThreeSecondEvent(Button pressedButton){
    #if TEST_RUN==2
        if(pressedButton == CENTER)
            iBinaryCounter = 0;
    #endif
}

void vApplicationTurnOnBinaryLed(int iCounter) {

    if (((iCounter >> 0) & 1) == HIGH)
        vLedTurnOn(SOLID_GREEN);
    else
        vLedTurnOff(SOLID_GREEN);

    if (((iCounter >> 1) & 1) == HIGH)
        vLedTurnOn(SOLID_YELLOW);
    else
        vLedTurnOff(SOLID_YELLOW);

    if (((iCounter >> 2) & 1) == HIGH)
        vLedTurnOn(DIM_RED);
    else
        vLedTurnOff(DIM_RED);

    if (((iCounter >> 3) & 1) == HIGH)
        vLedTurnOn(DIM_GREEN);
    else
        vLedTurnOff(DIM_GREEN);

    if (((iCounter >> 4) & 1) == HIGH)
        vLedTurnOn(DIM_BLUE);
    else
        vLedTurnOff(DIM_BLUE);
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
    vButtonsEventsInit(&xBoardButtons, &htim7, &htim16, &vButtonsEventCallbackPressedEvent, &vButtonsEventCallbackReleasedEvent, &vButtonsEventHalfSecondEvent, &vButtonsEventThreeSecondEvent);

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
    #if TEST_RUN==0
        vMatrixKeyboardInit(xKeyboardMapping, &htim6);
    #endif

    // Initialize UART Communication library
    vCommunicationStateMachineInit(&hlpuart1, &xSystemParameters);

    // Initialize Application
    while (1) {
        
        // TEST 1 - To Teste the assignment part 1, set the TEST_RUN preprocessor variable to 1

        // TEST 2 - To Teste the assignment part 2, set the TEST_RUN preprocessor variable to 2
        #if TEST_RUN==2
            vApplicationTurnOnBinaryLed(iBinaryCounter);
        #endif
    }
}
