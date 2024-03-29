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


static LedMapping (* boardLedArray)[NUMBER_BOARD_LEDS];


void vLedInit(LedMapping (*boardLeds)[NUMBER_BOARD_LEDS]){

	boardLedArray = boardLeds;
	unsigned char clockInUse = 0;

	for(int ledIndex = 0; ledIndex < 5; ledIndex++){

		if ((*boardLeds)[ledIndex].gpioPort == GPIOA)
			clockInUse |= 1 << 0;

		else if ((*boardLeds)[ledIndex].gpioPort == GPIOB)
			clockInUse |= 1 << 1;

		else if ((*boardLeds)[ledIndex].gpioPort == GPIOC)
			clockInUse |= 1 << 2;

		else if ((*boardLeds)[ledIndex].gpioPort == GPIOD)
			clockInUse |= 1 << 3;

		else if ((*boardLeds)[ledIndex].gpioPort == GPIOE)
			clockInUse |= 1 << 4;

		else if ((*boardLeds)[ledIndex].gpioPort == GPIOF)
			clockInUse |= 1 << 5;

		else if ((*boardLeds)[ledIndex].gpioPort == GPIOG)
			clockInUse |= 1 << 6;

		RCC->AHB2ENR |=  clockInUse;
		_SET_MODE_OUTPUT((*boardLeds)[ledIndex].gpioPort, (*boardLeds)[ledIndex].gpioPin);
	}


}

void vLedTurnOn(Color ledColor){

	(*boardLedArray)[ledColor].gpioPort->ODR |= (1 << (*boardLedArray)[ledColor].gpioPin);

}

void vLedTurnOff(Color ledColor){

	(*boardLedArray)[ledColor].gpioPort->ODR &= ~(1 << (*boardLedArray)[ledColor].gpioPin);
}

void vLedToggle(Color ledColor){

}

void vLedSet(Color ledColor, LedStatus status){

}
