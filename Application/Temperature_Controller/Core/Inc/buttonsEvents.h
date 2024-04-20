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
} Position;

typedef enum{
	CHANGED,
	NOT_CHANGED
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
	ChangeStatus change_status;
    unsigned int usTimeSpendPressed;
    char cThreeSecondsFlag;
} TimePressedInfo;

#define NUMBER_BOARD_BUTTONS 5

// ********************************************************** //
// Method name:        xButtonRead                            //
// Method description: Read   the   status  of  the  button   //
//                     (provided as a parameter) and returns  //
//                     its status as PRESSED or NOT_PRESSED   //
// Input params:       xButtonPosition                        //
//                        Position  of the button to be read, //
//                        as an enum                          //
// Output params:      ButtonStatus                           //
//                        The  status  of  the  button, as an //
//                        enum. PRESSED or NOT_PRESSED        //
// ********************************************************** //
ButtonStatus xButtonRead(Position xButtonPosition);

void vButtonsEventsInit(ButtonMapping (*xBoardButtonMapping)[NUMBER_BOARD_BUTTONS],TIM_HandleTypeDef* pDebounceTim, TIM_HandleTypeDef* pLongPressTim);
void vButtonsEventsGpioCallback(uint16_t GPIO_Pin);
#endif /* INC_BUTTON_H_ */
