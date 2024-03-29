// **********************************************//
// File name:        buttons.c                   //
// File description: This file implements the    //
//                   functions' implementations  //
//                   fot on-board Buttons        //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 29/Mar/2024                 //
// Revision date:    29/Mar/2024                 //
// **********************************************//

#include  "buttons.h"

#define _SET_MODE_INPUT(GPIO, PIN) \
				GPIO->MODER &= ~(1 << (PIN*2) );\
				GPIO->MODER &= ~(1 << (PIN*2 + 1) )

static ButtonMapping (*boardButtonArray)[NUMBER_BOARD_BUTTONS];


void vButtonInit(ButtonMapping (*boardButtons)[NUMBER_BOARD_BUTTONS]){

	boardButtonArray = boardButtons;
		unsigned char clockInUse = 0;

		for(int ButtonIndex = 0; ButtonIndex < NUMBER_BOARD_BUTTONS; ButtonIndex++){

			if ((*boardButtons)[ButtonIndex].gpioPort == GPIOA)
				clockInUse |= 1 << 0;

			else if ((*boardButtons)[ButtonIndex].gpioPort == GPIOB)
				clockInUse |= 1 << 1;

			else if ((*boardButtons)[ButtonIndex].gpioPort == GPIOC)
				clockInUse |= 1 << 2;

			else if ((*boardButtons)[ButtonIndex].gpioPort == GPIOD)
				clockInUse |= 1 << 3;

			else if ((*boardButtons)[ButtonIndex].gpioPort == GPIOE)
				clockInUse |= 1 << 4;

			else if ((*boardButtons)[ButtonIndex].gpioPort == GPIOF)
				clockInUse |= 1 << 5;

			else if ((*boardButtons)[ButtonIndex].gpioPort == GPIOG)
				clockInUse |= 1 << 6;

			RCC->AHB2ENR |=  clockInUse;
			_SET_MODE_INPUT((*boardButtons)[ButtonIndex].gpioPort, (*boardButtons)[ButtonIndex].gpioPin);
		}
}

ButtonStatus ButtonStatusRead(Position buttonPosition){
	return (((*boardButtonArray)[buttonPosition].gpioPort->IDR)>>((*boardButtonArray)[buttonPosition].gpioPin)) & 1;
}
