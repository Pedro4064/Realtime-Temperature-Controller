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

#include <main.h>
#include <usart.h>
#include <tim.h>

#include "application.h"
#include "heaterAndCooler.h"
#include "pwmConfig.h"

pwmConfig xHeaterConfig = {&htim1, TIM_CHANNEL_1};
pwmConfig xCoolerConfig = {&htim8, TIM_CHANNEL_1};

void vApplicationStart() {

	heaterAndCoolerInit(&xHeaterConfig, &xCoolerConfig);
	vHeaterSetPwmDuty(0.5);
	vCoolerFanSetPwmDuty(0.3);

	vHeaterStart();
	vCoolerStart();

    while (1) {

    }
}
