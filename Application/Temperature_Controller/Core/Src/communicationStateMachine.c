/*
 * communicationStateMachine.c
 *
 *  Created on: Apr 27, 2024
 *      Author: ES670 B
 */

#include <main.h>
#include "parser.h"

typedef enum {
    IDLE,
    READY,
    GET,
    SET,
    PARAM,
    VALUE
} State;

typedef enum {
    // Get Parameters ID
    TEMPERATURE_CURRENT = 't',
    VELOCITY_COOLER = 'v',

    // Set Parameters ID
    TEMPERATURE_TARGET = 't',
    DUTY_CYCLE_HEATER = 'h',
    DUTY_CYCLE_COOLER = 'c',
    BUTTON_LOCK = 'b',
} ParamID;

static State xCurrentState = IDLE;
static ParamID xTargetParam;
static unsigned char ucBufferIndex;
static UART_HandleTypeDef* pUartPeripheral;
static unsigned char ucCommByte;

void vStateHandleReady(){
    switch (ucCommByte)
    {
    case 'g':
        xCurrentState = GET;
        break;

    case 's':
        xCurrentState = SET;
        break;

    default:
        xCurrentState = IDLE;
        break;
    }
}

void vStateHandleGet(){
    switch (ucCommByte)
    {
    case TEMPERATURE_CURRENT:
    case VELOCITY_COOLER:

        xCurrentState = PARAM;
        xTargetParam  = ucCommByte;

        break;

    default:
        xCurrentState = IDLE;
        break;
    }
}

void vStateHandleSet(){
    
    switch (ucCommByte)
    {
        case TEMPERATURE_TARGET:
        case DUTY_CYCLE_COOLER:
        case DUTY_CYCLE_HEATER:
        case BUTTON_LOCK:
            xTargetParam = ucCommByte;
            xCurrentState = VALUE;
            ucBufferIndex = 0;
            break;
        
        default:
            xCurrentState = IDLE;
            break;
    }

}

void vStateHandleParam(){
    xCurrentState = IDLE;
    if(ucCommByte != ';')
        return;

    static char message[11];
    //! TODO - Add switch to set the variable float fTargetValue to the correct one (and add to the init a pointer to config struct)
    //! Maybe change the vParserFloatToString argument from a simple pointer to a pointer to a vector since the size is well established
    // vParserFloatToString(&message, )
        
        
}



void vCommunicationStateMachineProcessByte(){

    if(ucCommByte == '#'){
        xCurrentState = READY;
        return;
    }

    switch (xCurrentState)
    {
        case IDLE:
            return;
        
        case READY:
            vStateHandleReady();
            break;

        case GET:
            vStateHandleGet();
            break;

        case SET:
            vStateHandleSet();
            break;

        case PARAM:
            break;

        default:
            break;
    }

    HAL_UART_Receive_IT(pUartPeripheral, &ucCommByte, 1);
}

void vCommunicationStateMachineInit(UART_HandleTypeDef* pHUart){
    pUartPeripheral = pHUart;
    HAL_UART_Receive_IT(pUartPeripheral, &ucCommByte, 1);

}