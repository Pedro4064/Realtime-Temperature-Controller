// **********************************************//
// File name:        aplication.c                //
// File description: This file implements the    //
//                   temperature controller      //
//                   aplication layer.           //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 29/Mar/2024                 //
// Revision date:    29/Mar/2024                 //
// **********************************************//

#include <button.h>
#include "application.h"
#include "stm32g474xx.h"
#include "led.h"



void vApplicationStart(){

	// Initialize LED Drivers
	LedMapping xBoardLeds[] =
	{
				{GPIOA, LED_SOLID_GREEN_PIN },
				{GPIOA, LED_SOLID_YELLOW_PIN},
				{GPIOB, LED_DIM_RED_PIN     },
				{GPIOA, LED_DIM_GREEN_PIN   },
				{GPIOB, LED_DIM_BLUE_PIN    }
	};

	vLedInit(&xBoardLeds);

	// Initialize Button Drivers
	ButtonMapping xBoardButtons[] =
	{
				{GPIOC, BUTTON_UP_PIN    },
				{GPIOC, BUTTON_DOWN_PIN  },
				{GPIOC, BUTTON_LEFT_PIN  },
				{GPIOC, BUTTON_RIGHT_PIN },
				{GPIOB, BUTTON_CENTER_PIN}
	};

	vButtonInit(&xBoardButtons);
	int iDebug = 1;

	// Initialize Application
	while(1){
//		while(iDebug){

//			//Turn all the LEDs ON
//			vLedTurnOn(SOLID_GREEN);
//			vLedTurnOn(SOLID_YELLOW);
//			vLedTurnOn(DIM_RED);
//			vLedTurnOn(DIM_BLUE);
//			vLedTurnOn(DIM_GREEN);
//
//			HAL_Delay(500);
//
//			//Turn all the LEDs OFF
//			vLedTurnOff(SOLID_GREEN);
//			vLedTurnOff(SOLID_YELLOW);
//			vLedTurnOff(DIM_RED);
//			vLedTurnOff(DIM_BLUE);
//			vLedTurnOff(DIM_GREEN);
//
//			HAL_Delay(500);
//
//			//Toggle all the LEDs
//			vLedToggle(SOLID_GREEN);
//			vLedToggle(SOLID_YELLOW);
//			vLedToggle(DIM_BLUE);
//			vLedToggle(DIM_GREEN);
//			vLedToggle(DIM_RED);
//
//			HAL_Delay(500);
//
//			//Toggle all the LEDs
//			vLedToggle(SOLID_GREEN);
//			vLedToggle(SOLID_YELLOW);
//			vLedToggle(DIM_BLUE);
//			vLedToggle(DIM_GREEN);
//			vLedToggle(DIM_RED);
//
//			HAL_Delay(500);
//
//			//Set all the LEDs ON
//			vLedSet(SOLID_GREEN, ON);
//			vLedSet(SOLID_YELLOW, ON);
//			vLedSet(DIM_BLUE, ON);
//			vLedSet(DIM_GREEN, ON);
//			vLedSet(DIM_RED, ON);
//
//			HAL_Delay(500);
//
//			//Set all the LEDs OFF
//			vLedSet(SOLID_GREEN, OFF);
//			vLedSet(SOLID_YELLOW, OFF);
//			vLedSet(DIM_BLUE, OFF);
//			vLedSet(DIM_GREEN, OFF);
//			vLedSet(DIM_RED, OFF);
//
//			HAL_Delay(500);
//
//			iDebug = 0;
//		}
//
//
//		//READ BUTTONS TEST
//		if (xButtonRead(UP) == PRESSED)
//			vLedTurnOn(SOLID_GREEN);
//
//		if (xButtonRead(DOWN) == PRESSED)
//			vLedTurnOn(SOLID_YELLOW);
//
//		if (xButtonRead(LEFT) == PRESSED)
//			vLedTurnOn(DIM_BLUE);
//
//		if (xButtonRead(RIGHT) == PRESSED)
//			vLedTurnOn(DIM_GREEN);
//
//		if (xButtonRead(CENTER) == PRESSED)
//			vLedTurnOn(DIM_RED);
//
//		HAL_Delay(500);
//
//		//Set all the LEDs OFF
//		vLedSet(SOLID_GREEN, OFF);
//		vLedSet(SOLID_YELLOW, OFF);
//		vLedSet(DIM_BLUE, OFF);
//		vLedSet(DIM_GREEN, OFF);
//		vLedSet(DIM_RED, OFF);
//
//		HAL_Delay(500);

	}

}
