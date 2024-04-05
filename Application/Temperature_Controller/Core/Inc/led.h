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


// ********************************************************** //
// Method name:        vLedInit                               //
// Method description: Initialize   the   board's  LEDs  by   //
//                     enabling the clock of their GPIOs and  //
//                     setting their pins as outputs          //
// Input params:       xBoardLeds                             //
//                        Mapping of the boards LEDs to their //
//                        pins, ports and colors              //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vLedInit(LedMapping (*xBoardLeds)[NUMBER_BOARD_LEDS]);

// ********************************************************** //
// Method name:        vLedTurnOn                             //
// Method description: Turn on a specified LED provided as a  //
//                     parameter                              //
// Input params:       xLedColor                              //
//                        Color of the LED to be turned ON    //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vLedTurnOn(Color xledColor);


// ********************************************************** //
// Method name:        vLedTurnOff                            //
// Method description: Turn off a specified LED provided as   //
//                     a parameter                            //
// Input params:       xLedColor                              //
//                        Color of the LED to be turned OFF   //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vLedTurnOff(Color xledColor);

// ********************************************************** //
// Method name:        vLedToggle                             //
// Method description: Toggle the state of the specifiedLED   //
//                     (provided as a parameter) between ON   //
//                     and OFF                                //
// Input params:       xLedColor                              //
//                        Color of the LED to be toggled      //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vLedToggle(Color xledColor);

// ********************************************************** //
// Method name:        vLedSet                                //
// Method description: Configure   the  state  of  the  LED   //
//                     (provided  as  a  parameter)  to  be   //
//                     turned  on  or off, depending on the   //
//                     provided status parameter              //
// Input params:       xLedColor                              //
//                        Color of the LED to be configured   //
//                     xStatus                                //
//                        Status to set the LED to            //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vLedSet(Color xledColor, LedStatus xStatus);

#endif /* INC_LED_H_ */

