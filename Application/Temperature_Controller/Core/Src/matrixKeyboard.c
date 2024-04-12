/*
 * matrixKeyboard.c
 *
 *  Created on: Apr 5, 2024
 *      Author: ES670 B
 */

#include "matrixKeyboard.h"
#include "application.h"


#define CIRCULAR_INCREMENT(x) (x == 3) ? 0 : x+1

static MatrixMapping gpio_mapping;
static MatrixKeyboard xMatrixKeys;
static int cActiveColumn = 3;
static MatrixKeyboardTimePressed xTimerBalance;

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
    	xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].cThreeSecondsFlag = ((uiPreviously+10 >= 3000 || cPreviousThreeSecondFlag) && xKeyValue)? 1 : 0;
    	xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].usTimeSpendPressed = (xKeyValue == 0)? 0 : (uiPreviously + 10)%3000;

    	if (!cPreviousThreeSecondFlag && xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].cThreeSecondsFlag)
    		vMatrixKeyboardThreeSecPressedCallback(cVisualKeyboardMapping[i][cActiveColumn]);

    	if (!(xTimerBalance.xKeyboardTimePressed[i][cActiveColumn].usTimeSpendPressed % 500))
    		vMatrixKeyboardHalfSecPressedCallback(cVisualKeyboardMapping[i][cActiveColumn]);
    }

}

__weak vMatrixKeyboardThreeSecPressedCallback (char cKey){}
__weak vMatrixKeyboardHalfSecPressedCallback(char cKey){}



MatrixKeyboard* pMatrixKeyboardGetKeys() {
    return &xMatrixKeys;
}
