 // **********************************************//
// File name:        buzzer.h                    //
// File description: This file defines the       //
//                   drivers for the buzzers.    //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 21/Jun/2024                 //
// Revision date:    21/Jun/2024                 //
// **********************************************//



#ifndef INC_BUZZER_H__
#define INC_BUZZER_H__

#include "main.h"
#include "gpio.h"
#include "pwmConfig.h"

// ********************************************************** //
// Method name:        vBuzzerInit                            //
// Method description: Initialize the buzzer                  //
// Input params:       pBuzzerConfig                          //
//                        Pointer    to   the   configuraiton //
//                        structure    containing   the   PWM //
//                        parameters for the Buzzer           //
//                     pPeriodTim                             //
//                        Pointer   to   the   timer   handle //
//                        responsible for enable time         //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vBuzzerInit(pwmConfig* pBuzzerConfig, TIM_HandleTypeDef* pPeriodTim);

// ********************************************************** //
// Method name:        vBuzzerConfig                          //
// Method description: Configure the buzz frequency and the   //
//                     on-period for the next play            //
// Input params:       usFrequency                            //
//                        Buzz Frequency                      //
//                     usPeriod                               //
//                        On Period, in miliseconds           //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vBuzzerConfig(unsigned short int usFrequency, unsigned short int usPeriod);

// ********************************************************** //
// Method name:        vBuzzerPlay                            //
// Method description: Play  the  buzzer for the configured   //
//                     period on the configured frequency     //
// Input params:       void                                   //
//                        N/A                                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vBuzzerPlay(void);

// ********************************************************** //
// Method name:        vBuzzerStop                            //
// Method description: Stop the buzzer playing                //
// Input params:       void                                   //
//                        N/A                                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vBuzzerStop(void);

#endif