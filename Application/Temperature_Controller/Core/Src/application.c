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

#include "application.h"

#include <button.h>
#include <matrixKeyboard.h>

#include "led.h"
#include "stm32g474xx.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* timer) {
    if (timer->Instance == TIM6) {
        vMatrixKeyboardUpdateCallback();
    }
}

//A ideia seria ter uma entrada um numero de 5 bits e aih ligar a cor
void vApplicationTurnOnBinaryLed(MatrixKeyboard* pMatrixKeayboardStatus){
  	//Finds the key position pressed
    	int iKeyNumber = 0;
    	for(int i=1; i<=16; i++){
    	    if(pMatrixKeayboardStatus->cKeyboard1dValues[i-1] == 1){
    	    	iKeyNumber = i;
    	  }
    	}

    	if (((iKeyNumber >> 0) & 1) == HIGH)
    		vLedTurnOn(SOLID_GREEN);
    	else
    		vLedTurnOff(SOLID_GREEN);

    	if(((iKeyNumber>>1 ) & 1) == HIGH)
    		vLedTurnOn(SOLID_YELLOW);
    	else
    		vLedTurnOff(SOLID_YELLOW);

    	if(((iKeyNumber>>2 ) & 1) == HIGH)
    	    vLedTurnOn(DIM_RED);
    	else
    		vLedTurnOff(DIM_RED);

    	if(((iKeyNumber>>3 ) & 1) == HIGH)
    	    vLedTurnOn(DIM_GREEN);
    	else
    		vLedTurnOff(DIM_GREEN);

    	if(((iKeyNumber>>4 ) & 1) == HIGH)
    	    vLedTurnOn(DIM_BLUE);
    	else
    		vLedTurnOff(DIM_BLUE);
}

void vApplicationStart() {
    // Initialize LED Drivers
    LedMapping xBoardLeds[] =
        {
            {GPIOA, LED_SOLID_GREEN_PIN},
            {GPIOA, LED_SOLID_YELLOW_PIN},
            {GPIOB, LED_DIM_RED_PIN},
            {GPIOA, LED_DIM_GREEN_PIN},
            {GPIOB, LED_DIM_BLUE_PIN}};

    vLedInit(&xBoardLeds);

    // Initialize Button Drivers
    ButtonMapping xBoardButtons[] =
        {
            {GPIOC, BUTTON_UP_PIN},
            {GPIOC, BUTTON_DOWN_PIN},
            {GPIOC, BUTTON_LEFT_PIN},
            {GPIOC, BUTTON_RIGHT_PIN},
            {GPIOB, BUTTON_CENTER_PIN}};

    vButtonInit(&xBoardButtons);

    // Initialize Matrix Keyboard
    MatrixMapping xKeyboardMapping =
        {
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

    	//CODE TEST
    	MatrixKeyboard* pMatrixKeayboardStatus = pMatrixKeyboardGetKeys();

    	cKeyA = pMatrixKeayboardStatus->xKeyboard.cD;
    	vApplicationTurnOnBinaryLed(pMatrixKeayboardStatus);

    }
}
