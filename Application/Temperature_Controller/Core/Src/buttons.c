// **********************************************//
// File name:        button.c                   //
// File description: This file implements the    //
//                   functions' implementations  //
//                   fot on-board Buttons        //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 29/Mar/2024                 //
// Revision date:    29/Mar/2024                 //
// **********************************************//

#include <button.h>

#define _SET_MODE_INPUT(GPIO, PIN) \
				GPIO->MODER &= ~(1 << (PIN*2) );\
				GPIO->MODER &= ~(1 << (PIN*2 + 1) )

static ButtonMapping (*xBoardButtonArray)[NUMBER_BOARD_BUTTONS];


void vButtonInit(ButtonMapping (*xBoardButtons)[NUMBER_BOARD_BUTTONS]){

	xBoardButtonArray = xBoardButtons;
		unsigned char ucClockInUse = 0;

		for(int iButtonIndex = 0; iButtonIndex < NUMBER_BOARD_BUTTONS; iButtonIndex++){

			if ((*xBoardButtons)[iButtonIndex].xGpioPort == GPIOA)
				ucClockInUse |= 1 << 0;

			else if ((*xBoardButtons)[iButtonIndex].xGpioPort == GPIOB)
				ucClockInUse |= 1 << 1;

			else if ((*xBoardButtons)[iButtonIndex].xGpioPort == GPIOC)
				ucClockInUse |= 1 << 2;

			else if ((*xBoardButtons)[iButtonIndex].xGpioPort == GPIOD)
				ucClockInUse |= 1 << 3;

			else if ((*xBoardButtons)[iButtonIndex].xGpioPort == GPIOE)
				ucClockInUse |= 1 << 4;

			else if ((*xBoardButtons)[iButtonIndex].xGpioPort == GPIOF)
				ucClockInUse |= 1 << 5;

			else if ((*xBoardButtons)[iButtonIndex].xGpioPort == GPIOG)
				ucClockInUse |= 1 << 6;

			RCC->AHB2ENR |=  ucClockInUse;
			_SET_MODE_INPUT((*xBoardButtons)[iButtonIndex].xGpioPort, (*xBoardButtons)[iButtonIndex].cGpioPin);
		}
}

ButtonStatus bsButtonRead(Position xButtonPosition){
	return (((*xBoardButtonArray)[xButtonPosition].xGpioPort->IDR)>>((*xBoardButtonArray)[xButtonPosition].cGpioPin)) & 1;
}
