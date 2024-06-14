// **********************************************//
// File name:        button.h                   //
// File description: This file implements the    //
//                   functions' for driving      //
//                   on-board Buttons            //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 29/Mar/2024                 //
// Revision date:    29/Mar/2024                 //
// **********************************************//

#ifndef INC_BUTTONS_EVENTS_H_
#define INC_BUTTONS_EVENTS_H_

#include <stm32g474xx.h>
#include <stm32g4xx_hal.h>

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	CENTER
} Button;

typedef enum{
	NOT_CHANGED,
	CHANGED
} ChangeStatus;

typedef enum {
	LONG_PRESSED = 2,
	PRESSED = 1,
	NOT_PRESSED = 0
} ButtonStatus;

typedef struct{

	GPIO_TypeDef* xGpioPort;
	IRQn_Type xExtiModule;
	char cGpioPin;

}ButtonMapping;

typedef struct {
	ButtonStatus xStatus;
	ChangeStatus xChangeStatus;
    unsigned int usTimeSpendPressed;
    char cThreeSecondsFlag;
} PressedInfo;

#define NUMBER_BOARD_BUTTONS 5

// ********************************************************** //
// Method name:        vButtonsEventsInit                     //
// Method description: Initialize   all   the  buttons  and   //
//                     necessary  timers for long press and   //
//                     debounce functionalities               //
// Input params:       xBoardButtonMapping                    //
//                        The  array  responsible for mapping //
//                        the  Buttons to the Target mCU GPIO //
//                        Peripherals                         //
//                     pDebounceTim                           //
//                        Pointer to the timer responsiblefor //
//                        debouncing                          //
//                     pLongPressTim                          //
//                        Pointer to the timer responsiblefor //
//                        long press functionality            //
//                     pPressedCallback                       //
//                        Pointer to user defined callbackfor //
//                        handling simple button press        //
//                     pReleasedCallback                      //
//                        Pointer to user defined functionsto //
//                        handle  the  callback  from  simple //
//                        release of button                   //
//                     pHalfSecondCallback                    //
//                        Pointer  to  user  defined callback //
//                        function      of     Long     press //
//                        capacibilities (500ms)              //
//                     pThreeSecondCallback                   //
//                        Pointer  to  user  defined callback //
//                        function      of     Long     press //
//                        capacibilities (3s)                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vButtonsEventsInit(ButtonMapping (*xBoardButtonMapping)[NUMBER_BOARD_BUTTONS],TIM_HandleTypeDef* pDebounceTim, TIM_HandleTypeDef* pLongPressTim, void (*pPressedCallback)(Button), void (*pReleasedCallback)(Button), void (*pHalfSecondCallback)(Button),  void (*pThreeSecondCallback)(Button));

// ********************************************************** //
// Method name:        vButtonsEventsGpioCallback             //
// Method description: Callback  function  to  handle  GPIO   //
//                     Interrupt                              //
// Input params:       GPIO_Pin                               //
//                        GPIO Pin responsible for generating //
//                        the interrupt                       //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vButtonsEventsGpioCallback(uint16_t GPIO_Pin);

// ********************************************************** //
// Method name:        vButtonsEventsTimerCallback            //
// Method description: Callback  function  for dealing with   //
//                     both debounce and long press timers    //
// Input params:       timer                                  //
//                        Pointer to the timer responsiblefor //
//                        the interrupt                       //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vButtonsEventsTimerCallback(TIM_HandleTypeDef* timer);
#endif /* INC_BUTTON_H_ */
