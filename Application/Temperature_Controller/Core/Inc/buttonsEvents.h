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

void vButtonsEventsInit(ButtonMapping (*xBoardButtonMapping)[NUMBER_BOARD_BUTTONS],TIM_HandleTypeDef* pDebounceTim, TIM_HandleTypeDef* pLongPressTim, void (*pPressedCallback)(Button), void (*pReleasedCallback)(Button));
void vButtonsEventsGpioCallback(uint16_t GPIO_Pin);
void vButtonsEventsTimerCallback(TIM_HandleTypeDef* timer);
#endif /* INC_BUTTON_H_ */
