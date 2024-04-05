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

// ********************************************************** //
// Method name:        vButtonInit                            //
// Method description: Initialize  the  board's  buttons by   //
//                     enabling the clock of their GPIOsand   //
//                     setting their pins as inputs           //
// Input params:       xBoardButtons                          //
//                        Mapping   of  the  buttons  to  the //
//                        controller pins and ports           //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vButtonInit(ButtonMapping (*xBoardButtons)[NUMBER_BOARD_BUTTONS]);

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

#endif /* INC_BUTTON_H_ */
