// **********************************************//
// File name:        applicationScreen.h         //
// File description: This file defines the       //
//                   application Screens.        //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 21/Jun/2024                 //
// Revision date:    21/Jun/2024                 //
// **********************************************//




#include "application.h"
#include "lcd.h"

#ifndef INC_APPLICATION_SCREEN_H_
#define INC_APPLICATION_SCREEN_H_

// ********************************************************** //
// Method name:        vApplicationScreenInit                 //
// Method description: Initialize  the application`s Screen   //
//                     Service                                //
// Input params:       pLcdConfiguration                      //
//                        Pointer to the struct containing the//
//                        configurations necessary for driving//
//                        the LCD display                     //
//                     pAppParam                              //
//                        Pointer    to   the   application's //
//                        parameters,   used   to  both  read //
//                        information  to  be  displayed  and //
//                        request    actions    from    other //
//                        sub-systems                         //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vApplicationScreenInit(lcdConfig* pLcdConfiguration, applicationParameters* pAppParam);

// ********************************************************** //
// Method name:        vApplicationScreenUpdate               //
// Method description: Update the Screen states               //
// Input params:       void                                   //
//                        N/A                                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vApplicationScreenUpdate();

#endif