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
	LedMapping boardButtons[] =
	{
				{GPIOC, BUTTON_UP_PIN    },
				{GPIOC, BUTTON_DOWN_PIN  },
				{GPIOC, BUTTON_LEFT_PIN  },
				{GPIOC, BUTTON_RIGHT_PIN },
				{GPIOB, BUTTON_CENTER_PIN}
	};

	vButtonInit(&boardButtons);


	// Initialize Button Drivers
	while(1){

		//vLedTurnOn(SOLID_GREEN);
		//vLedTurnOn(SOLID_YELLOW);
		//vLedTurnOn(DIM_RED);
		//vLedTurnOn(DIM_BLUE);
		//vLedTurnOn(DIM_GREEN);

		//vLedTurnOff(SOLID_GREEN);
		//vLedTurnOff(SOLID_YELLOW);
		//vLedTurnOff(DIM_RED);
		//vLedTurnOff(DIM_BLUE);
		//vLedTurnOff(DIM_GREEN);

		vLedToggle(SOLID_GREEN);
		vLedToggle(SOLID_YELLOW);
		vLedToggle(DIM_BLUE);
		vLedToggle(DIM_GREEN);
		vLedToggle(DIM_RED);

		vLedSet(SOLID_GREEN, ON);

		vLedSet(SOLID_GREEN, OFF);

		vLedSet(SOLID_GREEN, ON);



	}

}
