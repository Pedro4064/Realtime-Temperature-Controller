/*
 * matrixKeyboard.h
 *
 *  Created on: Apr 5, 2024
 *      Author: ES670 B
 */
#include "stm32g4xx_hal.h"

#ifndef INC_MATRIXKEYBOARD_H_
#define INC_MATRIXKEYBOARD_H_

typedef enum {
    HIGH,
    LOW
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

void vMatrixKeyboardInit(MatrixMapping mapping, TIM_HandleTypeDef* timer);

void vMatrixKeyboardUpdateCallback();

MatrixKeyboard* pMatrixKeyboardGetKeys();

#endif /* INC_MATRIXKEYBOARD_H_ */
