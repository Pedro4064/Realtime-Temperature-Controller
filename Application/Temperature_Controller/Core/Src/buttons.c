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

#define _SET_MODE_INPUT(GPIO, PIN) \
				GPIO->MODER &= ~(1 << (PIN*2) );\
				GPIO->MODER &= ~(1 << (PIN*2 + 1) )

static ButtonMapping (*boardButtonArray)[NUMBER_BOARD_BUTTONS];


void vButtonInit(ButtonMapping (*boardButtons)[NUMBER_BOARD_BUTTONS]){

}

int iButtonRead(Position buttonPosition){

}
