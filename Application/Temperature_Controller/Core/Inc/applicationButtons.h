#ifndef H_APPLICATION_SCREEN_H_
#define H_APPLICATION_SCREEN_H_

#include <main.h>
#include "buttonsEvents.h"
#include "application.h"


void vApplicationButtonsInit(ButtonMapping (*pBoardButtonMapping)[NUMBER_BOARD_BUTTONS],TIM_HandleTypeDef* pDebounceTim, TIM_HandleTypeDef* pLongPressTim, applicationParameters* pApplicationParam);

#endif