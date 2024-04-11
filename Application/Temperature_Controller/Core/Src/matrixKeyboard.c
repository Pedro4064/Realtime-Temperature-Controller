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
        xMatrixKeys.cKeayboardValues[i][cActiveColumn] = HAL_GPIO_ReadPin(gpio_mapping.rows[i].xGpioPort, gpio_mapping.rows[i].cGpioPin);
    }

}

MatrixKeyboard* pMatrixKeyboardGetKeys() {
    return &xMatrixKeys;
}
