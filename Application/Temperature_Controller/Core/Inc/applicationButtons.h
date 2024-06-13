#include <main.h>

#include "buttonsEvents.h"
#include "application.h"

void vApplicationButtonsInit(ButtonMapping (*xBoardButtonMapping)[NUMBER_BOARD_BUTTONS],TIM_HandleTypeDef* pDebounceTim, TIM_HandleTypeDef* pLongPressTim, applicationParameters* pApplicationParam);