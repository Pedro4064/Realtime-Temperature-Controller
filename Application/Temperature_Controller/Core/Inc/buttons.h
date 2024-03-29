// **********************************************//
// File name:        buttons.h                   //
// File description: This file implements the    //
//                   functions' for driving      //
//                   on-board Buttons            //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 29/Mar/2024                 //
// Revision date:    29/Mar/2024                 //
// **********************************************//
#include "stm32g474xx.h"

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#define NUMBER_BOARD_BUTTONS 5

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

	GPIO_TypeDef* gpioPort;
	char gpioPin;

}ButtonMapping;

void vButtonInit(ButtonMapping (*boardButtons)[NUMBER_BOARD_BUTTONS]);
ButtonStatus ButtonStatusRead(Position buttonPosition);

#endif /* INC_BUTTONS_H_ */
