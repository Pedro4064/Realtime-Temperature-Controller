#include <main.h>

#include "application.h"
#include "buttonsEvents.h"

// ********************************************************** //
// Method name:        vApplicationButtonPressed              //
// Method description: Callback   function  for  pressed      //
//                     event                                  //
// Input params:       xPressedButton                         //
//                        Button  that caused the half second //
//                        long press event                    //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vApplicationButtonPressed(Button xPressedButton){}

// ********************************************************** //
// Method name:        vApplicationButtonReleased             //
// Method description: Callback   function  for  released     //
//                     event                                  //
// Input params:       xPressedButton                         //
//                        Button  that caused the half second //
//                        long press event                    //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vApplicationButtonReleased(Button xPressedButton){}

// ********************************************************** //
// Method name:        vApplicationButtonThreeSecondPressed   //
// Method description: Callback   function  for  the  three   //
//                     second long press event                //
// Input params:       xPressedButton                         //
//                        Button  that caused the half second //
//                        long press event                    //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vApplicationButtonThreeSecondPressed(Button xPressedButton){}

// ********************************************************** //
// Method name:        vApplicationButtonHalfSecondPressed    //
// Method description: Callback function for the button half  //
//                     second long press                      //
// Input params:       xPressedButton                         //
//                        Button  that caused the half second //
//                        long press event                    //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vApplicationButtonHalfSecondPressed(Button xPressedButton){}

void vApplicationButtonsInit(ButtonMapping (*xBoardButtonMapping)[NUMBER_BOARD_BUTTONS],TIM_HandleTypeDef* pDebounceTim, TIM_HandleTypeDef* pLongPressTim, applicationParameters* pApplicationParam){

	vButtonsEventsInit(xBoardButtonMapping, pDebounceTim, pLongPressTim, &vApplicationButtonPressed, &vApplicationButtonReleased, &vApplicationButtonHalfSecondPressed, &vApplicationButtonThreeSecondPressed);
}