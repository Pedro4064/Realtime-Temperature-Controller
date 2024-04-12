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
char cVisualKeyboardMapping = {
		{'1', '2', '3', 'A'},
		{'4', '5', '6', 'B'},
		{'7', '8', '9', 'C'},
		{'*', '0', '#', 'D'},
};

void vMatrixKeyboardInit(MatrixMapping mapping, TIM_HandleTypeDef* timer);

void vMatrixKeyboardUpdateCallback();

void vMatrixKeyboardThreeSecPressedCallback(char cKey);

void vMatrixKeyboardHalfSecPressedCallback(char cKey);

MatrixKeyboard* pMatrixKeyboardGetKeys();

#endif /* INC_MATRIXKEYBOARD_H_ */
