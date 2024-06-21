 // **********************************************//
// File name:        pwmConfig.h                 //
// File description: This file defines the       //
//                   config interfaces for pwm   //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 21/Jun/2024                 //
// Revision date:    21/Jun/2024                 //
// **********************************************//


#ifndef INC_PWM_CONFIG_H__
#define INC_PWM_CONFIG_H__

#include "main.h"

typedef struct PWM_CONFIG{
    TIM_HandleTypeDef* pTimeHandle;
    unsigned int uiChannel;
}pwmConfig;

#endif