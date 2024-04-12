// **********************************************//
// File name:        matrixKeyboard.c            //
// File description: This file implements the    //
//                   keyboard driver.            //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 12/Abr/2024                 //
// Revision date:    12/Abr/2024                 //
// **********************************************//
#include "matrixKeyboard.h"

#include "application.h"
#include "main.h"

#define CIRCULAR_INCREMENT(x) (x == 3) ? 0 : x + 1

static MatrixMapping gpio_mapping;
static MatrixKeyboard xMatrixKeys;
static int cActiveColumn = 3;
static MatrixKeyboardTimePressed xTimerBalance;

char cVisualKeyboardMapping[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

void vMatrixKeyboardInit(MatrixMapping mapping, TIM_HandleTypeDef* timer) {
    gpio_mapping = mapping;
    HAL_TIM_Base_Start_IT(timer);
}

void vMatrixKeyboardUpdateCallback() {
    HAL_GPIO_WritePin(gpio_mapping.columns[cActiveColumn].xGpioPort, gpio_mapping.columns[cActiveColumn].cGpioPin, GPIO_PIN_RESET);

    cActiveColumn = CIRCULAR_INCREMENT(cActiveColumn);

    HAL_GPIO_WritePin(gpio_mapping.columns[cActiveColumn].xGpioPort, gpio_mapping.columns[cActiveColumn].cGpioPin, GPIO_PIN_SET);

    // Iterate and read the status for each matrix row
    for (int i = 0; i <= 3; i++) {
        GPIO_PinState xKeyValue = HAL_GPIO_ReadPin(gpio_mapping.rows[i].xGpioPort, gpio_mapping.rows[i].cGpioPin);
        xMatrixKeys.cKeayboardValues[i][cActiveColumn] = xKeyValue;

        unsigned int uiPreviously = xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].usTimeSpendPressed;
        char cPreviousThreeSecondFlag = xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].cThreeSecondsFlag;
        xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].cThreeSecondsFlag = ((uiPreviously + 40 >= 3000 || cPreviousThreeSecondFlag) && xKeyValue) ? 1 : 0;
        xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].usTimeSpendPressed = (xKeyValue == 0) ? 0 : (uiPreviously + 40) % 3000;

        if (!cPreviousThreeSecondFlag && xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].cThreeSecondsFlag)
            vMatrixKeyboardThreeSecPressedCallback(cVisualKeyboardMapping[i][cActiveColumn]);

        if (xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].usTimeSpendPressed != 0 && !(xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].usTimeSpendPressed % 500))
            vMatrixKeyboardHalfSecPressedCallback(cVisualKeyboardMapping[i][cActiveColumn]);
    }
}

__weak void vMatrixKeyboardThreeSecPressedCallback(char cKey) {}
__weak void vMatrixKeyboardHalfSecPressedCallback(char cKey) {}

MatrixKeyboard* pMatrixKeyboardGetKeys() {
    return &xMatrixKeys;
}
