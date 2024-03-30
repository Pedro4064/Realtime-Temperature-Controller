// **********************************************//
// File name:        led.h                       //
// File description: This file implements the    //
//                   functions' for driving      //
//                   on-board LEDs               //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 22/Mar/2024                 //
// Revision date:    22/Mar/2024                 //
// **********************************************//

#ifndef INC_LED_H_
#define INC_LED_H_

typedef enum {
	SOLID_GREEN,
	SOLID_YELLOW,
	DIM_RED,
	DIM_GREEN,
	DIM_BLUE
} Color;

typedef enum {
	ON = 1,
	OFF = 0
} LedStatus;

typedef struct{

	GPIO_TypeDef* xGpioPort;
	char cGpioPin;

}LedMapping;


#define NUMBER_BOARD_LEDS 5


void vLedInit(LedMapping (*xBoardLeds)[NUMBER_BOARD_LEDS]);
void vLedTurnOn(Color xledColor);
void vLedTurnOff(Color xledColor);
void vLedToggle(Color xledColor);
void vLedSet(Color xledColor, LedStatus xStatus);

#endif /* INC_LED_H_ */

