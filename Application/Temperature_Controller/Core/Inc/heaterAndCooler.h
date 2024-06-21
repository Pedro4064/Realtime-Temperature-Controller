 // **********************************************//
// File name:        heaterAndCooler.h           //
// File description: This file defines the       //
//                   drivers for the heater      //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 21/Jun/2024                 //
// Revision date:    21/Jun/2024                 //
// **********************************************//



#ifndef INC_HEATER_AND_COOLER_H__
#define INC_HEATER_AND_COOLER_H__

#include "main.h"
#include "pwmConfig.h"

// ********************************************************** //
// Method name:        heaterAndCoolerInit                    //
// Method description: Initialize  the  Cooler  and Heating   //
//                     System                                 //
// Input params:       pHeaterConfig                          //
//                        Pointer to the configuration struct //
//                        for the heating element             //
//                     pCoolerConfig                          //
//                        Pointer to the struct for the Cooler//
//                        configuration                       //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void heaterAndCoolerInit(pwmConfig* pHeaterConfig, pwmConfig* pCoolerConfig);

// ********************************************************** //
// Method name:        vCoolerFanSetPwmDuty                   //
// Method description: Function for setting the duty-cycle    //
//                     of the PWM signal of the Cooler Fan    //
// Input params:       fCoolerPWM                             //
//                        Duty Cycle, between 0 - 1           //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vCoolerFanSetPwmDuty(float fCoolerPWM);

// ********************************************************** //
// Method name:        vHeaterSetPwmDuty                      //
// Method description: Function  for setting the duty-cycle   //
//                     of  the  PWM  signal  of the heating   //
//                     Element                                //
// Input params:       fHeaterPWM                             //
//                        Duty Cycle, between 0 - 1           //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vHeaterSetPwmDuty(float fHeaterPWM);

// ********************************************************** //
// Method name:        vCoolerStart                           //
// Method description: Function to start the cooler fan, by   //
//                     starting its driving PWM signal        //
// Input params:       void                                   //
//                        N/A                                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vCoolerStart(void);

// ********************************************************** //
// Method name:        vHeaterStart                           //
// Method description: Function   to   start   the  heating   //
//                     element, by starting its driving PWM   //
//                     signal                                 //
// Input params:       void                                   //
//                        N/A                                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vHeaterStart(void);

// ********************************************************** //
// Method name:        vCoolerStop                            //
// Method description: Function  to stop the cooler fan, by   //
//                     stopping its driving PWM signal        //
// Input params:       void                                   //
//                        N/A                                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vCoolerStop(void);

// ********************************************************** //
// Method name:        vHeaterStop                            //
// Method description: Function  to  turn  off  the heating   //
//                     element, by stopping its driving PWM   //
//                     Signal                                 //
// Input params:       void                                   //
//                        N/A                                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vHeaterStop(void);

#endif