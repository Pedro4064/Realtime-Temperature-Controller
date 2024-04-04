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

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "stm32g474xx.h"

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	CENTER
} Position;

typedef enum {
	PRESSED = 1,
	NOT_PRESSED = 0
} ButtonStatus;

typedef struct{

	GPIO_TypeDef* xGpioPort;
	char cGpioPin;

}ButtonMapping;

#define NUMBER_BOARD_BUTTONS 5

void vButtonInit(ButtonMapping (*xBoardButtons)[NUMBER_BOARD_BUTTONS]);
ButtonStatus xButtonRead(Position xButtonPosition);

#endif /* INC_BUTTON_H_ */
