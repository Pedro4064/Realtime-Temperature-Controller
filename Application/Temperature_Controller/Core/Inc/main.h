/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define BTN_UP_Pin GPIO_PIN_1
#define BTN_UP_GPIO_Port GPIOC
#define BTN_UP_EXTI_IRQn EXTI1_IRQn
#define BTN_DOWN_Pin GPIO_PIN_2
#define BTN_DOWN_GPIO_Port GPIOC
#define BTN_DOWN_EXTI_IRQn EXTI2_IRQn
#define BTN_LEFT_Pin GPIO_PIN_3
#define BTN_LEFT_GPIO_Port GPIOC
#define BTN_LEFT_EXTI_IRQn EXTI3_IRQn
#define LPUART1_TX_Pin GPIO_PIN_2
#define LPUART1_TX_GPIO_Port GPIOA
#define LPUART1_RX_Pin GPIO_PIN_3
#define LPUART1_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define BTN_RIGHT_Pin GPIO_PIN_4
#define BTN_RIGHT_GPIO_Port GPIOC
#define BTN_RIGHT_EXTI_IRQn EXTI4_IRQn
#define BTN_ENTER_Pin GPIO_PIN_5
#define BTN_ENTER_GPIO_Port GPIOC
#define KEYBOARD_L4_Pin GPIO_PIN_11
#define KEYBOARD_L4_GPIO_Port GPIOB
#define KEYBOARD_L3_Pin GPIO_PIN_12
#define KEYBOARD_L3_GPIO_Port GPIOB
#define KEYBOARD_L2_Pin GPIO_PIN_13
#define KEYBOARD_L2_GPIO_Port GPIOB
#define KEYBOARD_L1_Pin GPIO_PIN_15
#define KEYBOARD_L1_GPIO_Port GPIOB
#define KEYBOARD_C4_Pin GPIO_PIN_7
#define KEYBOARD_C4_GPIO_Port GPIOC
#define KEYBOARD_C3_Pin GPIO_PIN_8
#define KEYBOARD_C3_GPIO_Port GPIOC
#define KEYBOARD_C2_Pin GPIO_PIN_9
#define KEYBOARD_C2_GPIO_Port GPIOC
#define KEYBOARD_C1_Pin GPIO_PIN_10
#define KEYBOARD_C1_GPIO_Port GPIOA
#define T_SWDIO_Pin GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define T_SWO_Pin GPIO_PIN_3
#define T_SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern TIM_HandleTypeDef htim6;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
