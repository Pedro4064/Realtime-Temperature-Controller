#include "application.h"
#include "stm32g474xx.h"
#include "led.h"



void vApplicationMain(){

	// Initialize LED Drivers
	LedMapping boardLeds[] =
	{
				{GPIOA, LED_SOLID_GREEN_PIN },
				{GPIOA, LED_SOLID_YELLOW_PIN},
				{GPIOB, LED_DIM_RED_PIN     },
				{GPIOA, LED_DIM_GREEN_PIN   },
				{GPIOB, LED_DIM_BLUE_PIN    }
	};

	vLedInit(&boardLeds);

	// Initialize Button Drivers
	while(1){

		vLedTurnOn(SOLID_GREEN);
		vLedTurnOn(SOLID_YELLOW);
		vLedTurnOn(DIM_RED);
		vLedTurnOn(DIM_BLUE);
		vLedTurnOn(DIM_GREEN);


	}

}
