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

#include "matrixKeyboard.h"
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

typedef struct{
	float fTemperatureCurrent;
	float fTemperatureTarget;
	unsigned int uiVelocityCooler;
	unsigned char ucButtonLock;
	unsigned char ucDutyCycleCooler;
	unsigned char ucDutyCycleHeater;
}SystemParameters;

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

// ********************************************************** //
// Method name:        HAL_TIM_PeriodElapsedCallback          //
// Method description: Callback function for Hardware Timers  //
// Input params:       timer                                  //
//                        Pointer to the timmer that resulted //
//                        in the call of the function         //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* timer);

// ********************************************************** //
// Method name:        HAL_GPIO_EXTI_Callback                 //
// Method description: This  function  implements  the GPIO   //
//                     EXTI callback application.             //
// Input params:       GPIO_Pin                               //
//                        GPIO pin to be used.                //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

// ********************************************************** //
// Method name:        HAL_UART_RxCpltCallback                //
// Method description: This  function  implements  the UART   //
//                     message callback application.          //
// Input params:       pHUart                                 //
//                        Pointer  to  UART  peripheral to be //
//                        used.                               //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* pHUart);

// ********************************************************** //
// Method name:        vButtonsEventHalfSecondEvent           //
// Method description: This  function  implements the event   //
//                     triggered  when a specific button is   //
//                     pressed once							  //
// Input params:       pressedButton                          //
//                        Button that is pressed              //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vButtonsEventCallbackPressedEvent(Button pressedButton);

// ********************************************************** //
// Method name:        vButtonsEventHalfSecondEvent           //
// Method description: This  function  implements the event   //
//                     triggered  when a specific button is   //
//                     released. 							  //
// Input params:       pressedButton                          //
//                        Button that is pressed              //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vButtonsEventCallbackReleasedEvent(Button pressedButton);

// ********************************************************** //
// Method name:        vButtonsEventHalfSecondEvent           //
// Method description: This  function  implements the event   //
//                     triggered  when a specific button is   //
//                     pressed for more or equal than half a  //
//                     second.                                //
// Input params:       pressedButton                          //
//                        Button that is pressed              //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vButtonsEventHalfSecondEvent(Button pressedButton);

// ********************************************************** //
// Method name:        vButtonsEventHalfSecondEvent           //
// Method description: This  function  implements the event   //
//                     triggered  when a specific button is   //
//                     pressed for more or equal than three   //
//                     seconds.                               //
// Input params:       pressedButton                          //
//                        Button that is pressed              //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vButtonsEventThreeSecondEvent(Button pressedButton);

// ********************************************************** //
// Method name:        vApplicationTurnOnBinaryLed            //
// Method description: This  function,  given  an  integer,   //
//                     turns  on  the  LEDs  in  a  row  to   //
//                     represent a binary number.             //
// Input params:       iCounter                               //
//                        Number to be represented as a binary//
//                        number using LEDs                   //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vApplicationTurnOnBinaryLed(int iCounter);

#endif /* INC_APPLICATION_H_ */
