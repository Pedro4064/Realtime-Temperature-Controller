// **********************************************//
// File name:        applicationButtons.h        //
// File description: This file defines the       //
//                   application's buttons.      //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 21/Jun/2024                 //
// Revision date:    21/Jun/2024                 //
// **********************************************//



#ifndef H_APPLICATION_SCREEN_H_
#define H_APPLICATION_SCREEN_H_

#include <main.h>
#include "buttonsEvents.h"
#include "application.h"


// ********************************************************** //
// Method name:        vApplicationButtonsInit                //
// Method description: Initialize  the application's button   //
//                     interface                              //
// Input params:       pBoardButtonMapping                    //
//                        Pointer  to  struct  containing all //
//                        button mapping information          //
//                     pDebounceTim                           //
//                        Pointer to timer handle responsible //
//                        for debounce implementation         //
//                     pLongPressTim                          //
//                        Pointer to timer handle responsible //
//                        for  long  press  time tracking and //
//                        callback trigger                    //
//                     pApplicationParam                      //
//                        Pointer to application's parameters,//
//                        used  to  trigger  actions on other //
//                        sub-systems  from  press  and  long //
//                        press callbacks                     //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vApplicationButtonsInit(ButtonMapping (*pBoardButtonMapping)[NUMBER_BOARD_BUTTONS],TIM_HandleTypeDef* pDebounceTim, TIM_HandleTypeDef* pLongPressTim, applicationParameters* pApplicationParam);

#endif