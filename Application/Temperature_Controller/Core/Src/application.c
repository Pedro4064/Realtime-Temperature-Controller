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

#include <stm32g474xx.h>
#include <main.h>
#include <i2c.h>
#include <usart.h>
#include <tim.h>

#include "application.h"
#include "lcd.h"

LcdConfig pLcdConfiguration = {&hi2c1, 0x27};

void vApplicationStart() {
	vLcdInitLcd(&pLcdConfiguration);
    while (1) {
    	vLcdBacklightON();
    	vLcdWriteString("Teste Grupo B3");
		HAL_Delay(500);
    }
}
