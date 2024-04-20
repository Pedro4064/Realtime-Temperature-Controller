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

static TIM_HandleTypeDef* pDebounceTimer;
static TIM_HandleTypeDef* pLongPressTimer;
static ButtonMapping (*xBoardButtonArray)[NUMBER_BOARD_BUTTONS];
static TimePressedInfo xBoardButtonsPressedStatus[NUMBER_BOARD_BUTTONS];

void vButtonsEventsInit(ButtonMapping (*xBoardButtonMapping)[NUMBER_BOARD_BUTTONS],TIM_HandleTypeDef* pDebounceTim, TIM_HandleTypeDef* pLongPressTim){
    pDebounceTimer = pDebounceTim;
    pLongPressTimer= pLongPressTim;

    xBoardButtonArray = xBoardButtonMapping;
}

ButtonStatus xButtonRead(Position xButtonPosition){
	return (((*xBoardButtonArray)[xButtonPosition].xGpioPort->IDR)>>((*xBoardButtonArray)[xButtonPosition].cGpioPin)) & 1;
}

void vButtonsEventsGpioCallback(uint16_t GPIO_Pin){

    // Identify the index (on the gpio mapping and the corresponding time information array) 
    // of the button pressed, so we can disable the corresponding EXIT module as to
    // avoid multiple callback calls during debounce transition period.
    // It is important to point out that the buttons MUST NOT be connect to a pin of same number, 
    // even from different ports, since the target MCU architecture is not able to differentiate 
    // between GPIO interrupts based on ports, only pins. This is the reason why we can use only
    // the position of the pin on the user defined GPIO mapping to determine which button is pressed.
    int iPressedButtonIndex = iGetButtonIndex(GPIO_Pin);
    HAL_NVIC_DisableIRQ(xBoardButtonArray[iPressedButtonIndex]->xExtiModule);
    xBoardButtonsPressedStatus[iPressedButtonIndex].change_status = CHANGED;

    pDebounceTimer->Instance->CNT = 0;
    HAL_TIM_Base_Start_IT(pDebounceTimer);
}

void vButtonsEventsTimerDebounceCallback(){

}

inline int iGetButtonIndex(uint16_t GPIO_Pin){
    for (int iButtonIndex = 0; iButtonIndex < NUMBER_BOARD_BUTTONS; iButtonIndex++)
    {
        if (xBoardButtonArray[iButtonIndex]->cGpioPin == GPIO_Pin)
            return iButtonIndex;
        
    }

    return 0;
    
}