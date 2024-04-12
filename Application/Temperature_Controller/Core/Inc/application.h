// **********************************************//
// File name:        aplication.h                //
// File description: This file declare functions //
//                   interface and data types for//
//                   aplication.                 //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 29/Mar/2024                 //
// Revision date:    29/Mar/2024                 //
// **********************************************//
#include <main.h>

#include "stm32g4xx_hal.h"

#ifndef INC_APPLICATION_H_
#define INC_APPLICATION_H_

#define LED_SOLID_GREEN_PIN 5
#define LED_SOLID_YELLOW_PIN 4
#define LED_DIM_RED_PIN 14
#define LED_DIM_GREEN_PIN 12
#define LED_DIM_BLUE_PIN 5

#define BUTTON_UP_PIN 1
#define BUTTON_DOWN_PIN 2
#define BUTTON_LEFT_PIN 3
#define BUTTON_RIGHT_PIN 4
#define BUTTON_CENTER_PIN 0

#define KEYBOARD_L4_Pin GPIO_PIN_11
#define KEYBOARD_L3_Pin GPIO_PIN_12
#define KEYBOARD_L2_Pin GPIO_PIN_13
#define KEYBOARD_L1_Pin GPIO_PIN_15

#define KEYBOARD_L4_GPIO_Port GPIOB
#define KEYBOARD_L3_GPIO_Port GPIOB
#define KEYBOARD_L2_GPIO_Port GPIOB
#define KEYBOARD_L1_GPIO_Port GPIOB

#define KEYBOARD_C4_Pin GPIO_PIN_7
#define KEYBOARD_C3_Pin GPIO_PIN_8
#define KEYBOARD_C2_Pin GPIO_PIN_9
#define KEYBOARD_C1_Pin GPIO_PIN_10

#define KEYBOARD_C3_GPIO_Port GPIOC
#define KEYBOARD_C4_GPIO_Port GPIOC
#define KEYBOARD_C2_GPIO_Port GPIOC
#define KEYBOARD_C1_GPIO_Port GPIOA

// ********************************************************** //
// Method name:        vApplicationStart                      //
// Method description: All   the   code   responsible   for   //
//                     implementing     the     temperature   //
//                     controller application, allowing the   //
//                     main  function  to  focus  solely on   //
//                     calling this function for execution    //
// Input params:       void                                   //
//                        N/A                                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vApplicationStart();

void vApplicationTurnOnBinaryLed(MatrixKeyboard* pMatrixKeayboardStatus);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* timer);
#endif /* INC_APPLICATION_H_ */
