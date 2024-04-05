// **********************************************//
// File name:        aplication.h                //
// File description: This file declare functions //
//                   interface and data types for//
//                   aplication.                 //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 29/Mar/2024                 //
// Revision date:    29/Mar/2024                 //
// **********************************************//

#ifndef INC_APPLICATION_H_
#define INC_APPLICATION_H_

#define LED_SOLID_GREEN_PIN  5
#define LED_SOLID_YELLOW_PIN 4
#define LED_DIM_RED_PIN     14
#define LED_DIM_GREEN_PIN   12
#define LED_DIM_BLUE_PIN     5

#define BUTTON_UP_PIN		 1
#define BUTTON_DOWN_PIN		 2
#define BUTTON_LEFT_PIN		 3
#define BUTTON_RIGHT_PIN     4
#define BUTTON_CENTER_PIN    0

// ********************************************************** //
// Method name:        vApplicationStart                      //
// Method description: All   the   code   responsible   for   //
//                     implementing     the     temperature   //
//                     controller application, allowing the   //
//                     main  function  to  focus  solely on   //
//                     calling this function for execution    //
// Input params:       void                                   //
//                        N/A                                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vApplicationStart();

#endif /* INC_APPLICATION_H_ */
