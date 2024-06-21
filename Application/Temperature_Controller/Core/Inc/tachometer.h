 // **********************************************//
// File name:        tachometer.h                //
// File description: This file defines           //
//                   the tachometer system       //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 21/Jun/2024                 //
// Revision date:    21/Jun/2024                 //
// **********************************************//



#include "main.h"

#ifndef INC_H_TACHOMETER__
#define INC_H_TACHOMETER__

extern float fTachometerMeasuredSpeed;

// ********************************************************** //
// Method name:        vTachometerInit                        //
// Method description: Initialize  all  the necessary timers  //
//                     for the tachometer operation           //
// Input params:       pEnableTim                             //
//                        Pointer   to   the   timer   handle //
//                        responsible  by  the  enable signal //
//                        (the  tachometer  uses fixed window //
//                        frequency counting)                 //
//                     pCounterTim                            //
//                        Pointer   to   the   timer   handle //
//                        responsible  for the counter update //
//                        (for  the  fixed  window  frequency //
//                        counter algorithm)                  //
//                     uiEnablePeriod                         //
//                        Period, in ms, of the enable period //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vTachometerInit(TIM_HandleTypeDef* pEnableTim, TIM_HandleTypeDef* pCounterTim, unsigned int uiEnablePeriod);

// ********************************************************** //
// Method name:        vTachometerStartReadings               //
// Method description: Start  the  tachometer  readings  by   //
//                     starting the enable timer (the value   //
//                     shall  be  calculate  on  the  timer   //
//                     callback function)                     //
// Input params:       void                                   //
//                        N/A                                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vTachometerStartReadings(void);

// ********************************************************** //
// Method name:        vTachometerUpdateSpeed                 //
// Method description: Calculate the speed from the captured  //
//                     pulses      and      update      the   //
//                     fTachometerMeasuredSpeed   variable.   //
//                     This function shall be called in the   //
//                     timer callback                         //
// Input params:       void                                   //
//                        N/A                                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vTachometerUpdateSpeed(void);
#endif