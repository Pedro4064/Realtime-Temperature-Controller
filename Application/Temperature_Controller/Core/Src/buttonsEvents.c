// **********************************************//
// File name:        buttonsEvents.c             //
// File description: This file implements the    //
//                   buttons driver, with        //
//                   debouncing and log press    //
//                   functionality.              //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 19/Abr/2024                 //
// Revision date:    19/Abr/2024                 //
// **********************************************//

#include "buttonsEvents.h"
#include <gpio.h>

#define FALSE 0
#define TRUE  1

static TIM_HandleTypeDef* pDebounceTimer;
static TIM_HandleTypeDef* pLongPressTimer;

static ButtonMapping (*xBoardButtonArray)[NUMBER_BOARD_BUTTONS];
static PressedInfo xBoardButtonsPressedStatus[NUMBER_BOARD_BUTTONS];

static void (*pButtonPressedCallback)(Button);
static void (*pButtonReleasedCallback)(Button);

static void (*pButtonHalfSecondCallback)(Button);
static void (*pButtonThreeSecondCallback)(Button);

void vButtonsEventsInit(ButtonMapping (*xBoardButtonMapping)[NUMBER_BOARD_BUTTONS],TIM_HandleTypeDef* pDebounceTim, TIM_HandleTypeDef* pLongPressTim, void (*pPressedCallback)(Button), void (*pReleasedCallback)(Button), void (*pHalfSecondCallback)(Button),  void (*pThreeSecondCallback)(Button)){
    pDebounceTimer = pDebounceTim;
    pLongPressTimer= pLongPressTim;

    xBoardButtonArray = xBoardButtonMapping;

    pButtonPressedCallback = pPressedCallback;
    pButtonReleasedCallback= pReleasedCallback;

    pButtonHalfSecondCallback = pHalfSecondCallback;
    pButtonThreeSecondCallback= pThreeSecondCallback;
}


int iGetButtonIndex(uint16_t GPIO_Pin){
    for (int iButtonIndex = 0; iButtonIndex < NUMBER_BOARD_BUTTONS; iButtonIndex++)
    {
        if ((*xBoardButtonArray)[iButtonIndex].cGpioPin == GPIO_Pin)
            return iButtonIndex;
        
    }

    return 0;
    
}

void vButtonsEventsGpioCallback(uint16_t GPIO_Pin){
    /* Identify the index (on the gpio mapping and the corresponding time information array) 
     of the button pressed, so we can disable the corresponding EXIT module as to
     avoid multiple callback calls during debounce transition period (it shall be enabled again at the end of transition period timer of 10ms).
       It is important to point out that the buttons MUST NOT be connect to a pin of same number, 
     even from different ports, since the target MCU architecture is not able to differentiate 
     between GPIO interrupts based on ports, only pins. This is the reason why we can use only
     the position of the pin on the user defined GPIO mapping to determine which button is pressed.
    */
    int iPressedButtonIndex = iGetButtonIndex(GPIO_Pin);
    HAL_NVIC_DisableIRQ((*xBoardButtonArray)[iPressedButtonIndex].xExtiModule);
    xBoardButtonsPressedStatus[iPressedButtonIndex].xChangeStatus = CHANGED;

    /*  Furthermore, since we disable the NVIC capabilities from the peripheral after the first call, 
      any further callback calls shall be from a different button that was first pressed (or unpressed).
        When that is the case, since we will not use one timer per button, the current counting timer
      shall be zeroed (since this is for HMI purpose only, the worst case scenario of all buttons being
      pressed right before the end of the count up has no impact on safety) as to ensure a minimum debounce
      time for all pressed events.
    */
    //__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
    pDebounceTimer->Instance->CNT = 0;
    HAL_TIM_Base_Start_IT(pDebounceTimer);
    HAL_TIM_Base_Start_IT(pLongPressTimer);
}

void vButtonsEventsSinglePressCallback(){
	HAL_TIM_Base_Stop_IT(pDebounceTimer);
    for (int iButtonIndex = 0; iButtonIndex < NUMBER_BOARD_BUTTONS; iButtonIndex++){

            if (xBoardButtonsPressedStatus[iButtonIndex].xChangeStatus == NOT_CHANGED)
                continue;

            ButtonMapping xCurrentButton = (*xBoardButtonArray)[iButtonIndex];
            xBoardButtonsPressedStatus[iButtonIndex].xStatus = HAL_GPIO_ReadPin(xCurrentButton.xGpioPort, xCurrentButton.cGpioPin);

            if(xBoardButtonsPressedStatus[iButtonIndex].xStatus == PRESSED)
                (*pButtonPressedCallback)(iButtonIndex);
            else 
                (*pButtonReleasedCallback)(iButtonIndex);

            
            xBoardButtonsPressedStatus[iButtonIndex].xChangeStatus = NOT_CHANGED;
            __HAL_GPIO_EXTI_CLEAR_IT((*xBoardButtonArray)[iButtonIndex].cGpioPin);
            HAL_NVIC_EnableIRQ((*xBoardButtonArray)[iButtonIndex].xExtiModule);
        }

    }

void vButtonsEventsLongPressCallback(){

    char cPressedButtons = FALSE;
    GPIO_PinState xIsPressed;
    for (int iButtonIndex = 0; iButtonIndex < NUMBER_BOARD_BUTTONS; iButtonIndex++){

        xIsPressed = HAL_GPIO_ReadPin((*xBoardButtonArray)[iButtonIndex].xGpioPort, (*xBoardButtonArray)[iButtonIndex].cGpioPin);
        unsigned int uiPreviousePressedTime = xBoardButtonsPressedStatus[iButtonIndex].usTimeSpendPressed;
        char cPreviouseThreeSecondFlag = xBoardButtonsPressedStatus[iButtonIndex].cThreeSecondsFlag;

        xBoardButtonsPressedStatus[iButtonIndex].cThreeSecondsFlag = ((uiPreviousePressedTime + 10 >= 3000 || cPreviouseThreeSecondFlag) && xIsPressed) ? 1:0;
        xBoardButtonsPressedStatus[iButtonIndex].usTimeSpendPressed = (!xIsPressed) ? 0 : (uiPreviousePressedTime + 10) % 3000;

        if (!cPreviouseThreeSecondFlag && xBoardButtonsPressedStatus[iButtonIndex].cThreeSecondsFlag)
            (*pButtonHalfSecondCallback)(iButtonIndex);

        if (xBoardButtonsPressedStatus[iButtonIndex].usTimeSpendPressed != 0 && !(xBoardButtonsPressedStatus[iButtonIndex].usTimeSpendPressed % 500))
            (*pButtonThreeSecondCallback)(iButtonIndex);

        cPressedButtons |= xIsPressed;
    }

    if (!xIsPressed)
        HAL_TIM_Base_Stop_IT(pLongPressTimer);
    
}

void vButtonsEventsTimerCallback(TIM_HandleTypeDef* timer){

    if (timer == pDebounceTimer)
        vButtonsEventsSinglePressCallback();
    else 
        vButtonsEventsLongPressCallback();
}

