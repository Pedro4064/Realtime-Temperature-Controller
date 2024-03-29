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


#define NUMBER_BOARD_LEDS 5


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

	GPIO_TypeDef* gpioPort;
	char gpioPin;

}LedMapping;


void vLedInit(LedMapping (*boardLeds)[NUMBER_BOARD_LEDS]);
void vLedTurnOn(Color ledColor);
void vLedTurnOff(Color ledColor);
void vLedToggle(Color ledColor);
void vLedSet(Color ledColor, LedStatus status);

#endif /* INC_LED_H_ */
