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

#define CIRCULAR_INCREMENT(x) (x == 3) ? 0 : x + 1

static queue* pKeyboardQueue;
static MatrixMapping xGpioMapping;
static MatrixKeyboard xMatrixKeys;
static MatrixKeyboardTimePressed xTimerBalance;

static int cActiveColumn = 3;
char cVisualKeyboardMapping[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

void vMatrixKeyboardInit(MatrixMapping xMapping, TIM_HandleTypeDef* pTimer, queue* pKeyQueue) {
    xGpioMapping = xMapping;
    pKeyboardQueue = pKeyQueue;
    HAL_TIM_Base_Start_IT(pTimer);
}

void vMatrixKeyboardUpdateCallback() {
    HAL_GPIO_WritePin(xGpioMapping.columns[cActiveColumn].xGpioPort, xGpioMapping.columns[cActiveColumn].cGpioPin, GPIO_PIN_RESET);

    cActiveColumn = CIRCULAR_INCREMENT(cActiveColumn);

    HAL_GPIO_WritePin(xGpioMapping.columns[cActiveColumn].xGpioPort, xGpioMapping.columns[cActiveColumn].cGpioPin, GPIO_PIN_SET);

    // Iterate and read the status for each matrix row
    for (int i = 0; i <= 3; i++) {
        // Read the GPIO values and save its state
        GPIO_PinState xKeyValue = HAL_GPIO_ReadPin(xGpioMapping.rows[i].xGpioPort, xGpioMapping.rows[i].cGpioPin);
        xMatrixKeys.cKeayboardValues[i][cActiveColumn] = xKeyValue;

        // If a key was pressed, add it to the keyboard's keystrokes buffer/queue
        if(xKeyValue)
            vQueueInsert(pKeyboardQueue, cVisualKeyboardMapping[i][cActiveColumn]);

        // Determine Long and Longer press for the button
        unsigned int uiPreviously = xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].usTimeSpendPressed;
        char cPreviousThreeSecondFlag = xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].cThreeSecondsFlag;
        xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].cThreeSecondsFlag = ((uiPreviously + 40 >= 3000 || cPreviousThreeSecondFlag) && xKeyValue) ? 1 : 0;
        xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].usTimeSpendPressed = (xKeyValue == 0) ? 0 : (uiPreviously + 40) % 3000;

        if (!cPreviousThreeSecondFlag && xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].cThreeSecondsFlag)
            vMatrixKeyboardThreeSecPressedCallback(cVisualKeyboardMapping[i][cActiveColumn]);

        if (xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].usTimeSpendPressed != 0 && !((xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].usTimeSpendPressed + 40) % 500))
            vMatrixKeyboardHalfSecPressedCallback(cVisualKeyboardMapping[i][cActiveColumn]);
    }
}

__weak void vMatrixKeyboardThreeSecPressedCallback(char cKey) {}
__weak void vMatrixKeyboardHalfSecPressedCallback(char cKey) {}

MatrixKeyboard* pMatrixKeyboardGetKeys() {
    return &xMatrixKeys;
}
