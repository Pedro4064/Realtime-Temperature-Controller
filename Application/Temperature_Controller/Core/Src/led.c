// **********************************************//
// File name:        led.c                       //
// File description: This file implements the    //
//                   functions' implementations  //
//                   fot on-board LEDs           //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 22/Mar/2024                 //
// Revision date:    22/Mar/2024                 //
// **********************************************//
#include "stm32g474xx.h"
#include "led.h"


#define _SET_MODE_OUTPUT(GPIO, PIN) \
				GPIO->MODER |= (1 << (PIN*2) );\
				GPIO->MODER &= ~(1 << (PIN*2 + 1) )


static LedMapping (*xBoardLedArray)[NUMBER_BOARD_LEDS];


void vLedInit(LedMapping (*xBoardLeds)[NUMBER_BOARD_LEDS]){

	xBoardLedArray = xBoardLeds;
	unsigned char ucClockInUse = 0;

	for(int iLedIndex = 0; iLedIndex < 5; iLedIndex++){

		if ((*xBoardLeds)[iLedIndex].xGpioPort == GPIOA)
			ucClockInUse |= 1 << 0;

		else if ((*xBoardLeds)[iLedIndex].xGpioPort == GPIOB)
			ucClockInUse |= 1 << 1;

		else if ((*xBoardLeds)[iLedIndex].xGpioPort == GPIOC)
			ucClockInUse |= 1 << 2;

		else if ((*xBoardLeds)[iLedIndex].xGpioPort == GPIOD)
			ucClockInUse |= 1 << 3;

		else if ((*xBoardLeds)[iLedIndex].xGpioPort == GPIOE)
			ucClockInUse |= 1 << 4;

		else if ((*xBoardLeds)[iLedIndex].xGpioPort == GPIOF)
			ucClockInUse |= 1 << 5;

		else if ((*xBoardLeds)[iLedIndex].xGpioPort == GPIOG)
			ucClockInUse |= 1 << 6;

		RCC->AHB2ENR |=  ucClockInUse;
		_SET_MODE_OUTPUT((*xBoardLeds)[iLedIndex].xGpioPort, (*xBoardLeds)[iLedIndex].cGpioPin);
	}
}

inline void vLedTurnOn(Color xLedColor){

	(*xBoardLedArray)[xLedColor].xGpioPort->ODR |= (1 << (*xBoardLedArray)[xLedColor].cGpioPin);
}

inline void vLedTurnOff(Color xLedColor){

	(*xBoardLedArray)[xLedColor].xGpioPort->ODR &= ~(1 << (*xBoardLedArray)[xLedColor].cGpioPin);
}

inline void vLedToggle(Color xLedColor){

	(*xBoardLedArray)[xLedColor].xGpioPort->ODR ^= (1 << (*xBoardLedArray)[xLedColor].cGpioPin);
}

void vLedSet(Color xLedColor, LedStatus xStatus){

	if(xStatus == ON){
		vLedTurnOn(xLedColor);
	}
	else{
		vLedTurnOff(xLedColor);
	}
}
