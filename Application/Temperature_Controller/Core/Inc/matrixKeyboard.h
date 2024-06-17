// **********************************************//
// File name:        matrixKeyboard.h            //
// File description: This file implements the    //
//                   keyboard driver.            //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 12/Abr/2024                 //
// Revision date:    12/Abr/2024                 //
// **********************************************//
#include "stm32g4xx_hal.h"
#include "queue.h"

#ifndef INC_MATRIXKEYBOARD_H_
#define INC_MATRIXKEYBOARD_H_

typedef enum {
    HIGH = 1,
    LOW = 0
} KeyStatus;

typedef struct {
    char cOne;
    char cTwo;
    char cThree;
    char cA;

    char cFour;
    char cFive;
    char cSix;
    char cB;

    char cSeven;
    char cEight;
    char cNine;
    char cC;

    char cAsterisk;
    char cZero;
    char cHashtag;
    char cD;
} KeyboardKeys;

typedef struct {
    unsigned int usTimeSpendPressed;
    char cThreeSecondsFlag;
} TimePressedStatus;

typedef struct {
    TimePressedStatus xOne;
    TimePressedStatus xTwo;
    TimePressedStatus xThree;
    TimePressedStatus xA;

    TimePressedStatus xFour;
    TimePressedStatus xFive;
    TimePressedStatus xSix;
    TimePressedStatus xB;

    TimePressedStatus xSeven;
    TimePressedStatus xEight;
    TimePressedStatus xNine;
    TimePressedStatus xC;

    TimePressedStatus xAsterisk;
    TimePressedStatus xZero;
    TimePressedStatus xHashtag;
    TimePressedStatus xD;
} KeyboardTimePressedStatus;

typedef union {
    KeyboardTimePressedStatus xKeyboard;
    TimePressedStatus xKeyboardTimePressed[4][4];
} MatrixKeyboardTimePressed;

typedef union {
    KeyboardKeys xKeyboard;
    char cKeayboardValues[4][4];
    char cKeyboard1dValues[16];
} MatrixKeyboard;

typedef struct {
    GPIO_TypeDef* xGpioPort;
    unsigned int cGpioPin;

} MatrixGpioInterface;

typedef struct {
    MatrixGpioInterface columns[4];
    MatrixGpioInterface rows[4];

} MatrixMapping;
// MatrixKeyboard matrix_keyboard;
// matrix_keyboard.xKeyboard.cB;
// matrix_keyboard.cKeayboardValues[1][3]

// ********************************************************** //
// Method name:        vMatrixKeyboardInit                    //
// Method description: Initialize   the   Matrix   Keyboard   //
//                     module, using the specified timerand   //
//                     GPIO mapping.                          //
// Input params:       mapping                                //
//                        GPIO    Mapping,   represents   the //
//                        connection  between  the matrix and //
//                        MCU                                 //
//                     timer                                  //
//                        Pointer  to  the timer to use duing //
//                        pulling                             //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vMatrixKeyboardInit(MatrixMapping mapping, TIM_HandleTypeDef* timer, queue* pKeyQueue);

// ********************************************************** //
// Method name:        vMatrixKeyboardUpdateCallback          //
// Method description: Callback to update the values ofeach   //
//                     key                                    //
// Input params:                                              //
//                                                            //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vMatrixKeyboardUpdateCallback();

// ********************************************************** //
// Method name:        vMatrixKeyboardThreeSecPressedCallback //
// Method description: Callback function of the longer press  //
//                     (3 seconds)                            //
// Input params:       cKey                                   //
//                        ASCII  Representation  of  the  key //
//                        pressed (follows the same patter as //
//                        printed on the keyboard)            //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vMatrixKeyboardThreeSecPressedCallback(char cKey);

// ********************************************************** //
// Method name:        vMatrixKeyboardHalfSecPressedCallback  //
// Method description: Callback  function to the long press   //
//                     (0.5 seconds)                          //
// Input params:       cKey                                   //
//                        ASCII  Representation  of  the  key //
//                        pressed (follows the same patter as //
//                        printed on the keyboard)            //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vMatrixKeyboardHalfSecPressedCallback(char cKey);

// ********************************************************** //
// Method name:        pMatrixKeyboardGetKeys                 //
// Method description: Get a union  containing the values of  //
//                     all  keys  (1  for pressed and 0 for   //
//                     unpressed)                             //
// Input params:                                              //
//                                                            //
// Output params:      MatrixKeyboard                         //
//                        Pointer  to  the union representing //
//                        all the values of the keys          //
// ********************************************************** //
MatrixKeyboard* pMatrixKeyboardGetKeys();

#endif /* INC_MATRIXKEYBOARD_H_ */
