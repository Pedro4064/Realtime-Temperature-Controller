/*
 * communicationStateMachine.c
 *
 *  Created on: Apr 27, 2024
 *      Author: ES670 B
 */

#include <main.h>
#include "parser.h"
#include "application.h"

#define VALIDATED_INPUT(x) ((x >= '0' && x <= '9') || x == ',')
#define MAX_BUFFER_SIZE 7

typedef enum {
    IDLE,
    READY,
    GET,
    VAL_SET,
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
static UART_HandleTypeDef* pUartPeripheral;
static unsigned char ucCommByte;

static SystemParameters* pSystemParameters;

void vStateHandleReady(){
    switch (ucCommByte)
    {
    case 'g':
        xCurrentState = GET;
        break;

    case 's':
        xCurrentState = VAL_SET;
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
    float fTargetValue;

    switch (xTargetParam)
    {
    case TEMPERATURE_CURRENT:
        fTargetValue = (*pSystemParameters).fTemperatureCurrent;
        break;

    case VELOCITY_COOLER:
        fTargetValue = (float)(*pSystemParameters).uiVelocityCooler;
        break;
    
    default:
        return;
        break;
    }

    vParserFloatToString(&message, fTargetValue);
    HAL_UART_Transmit_IT(pUartPeripheral, message, 11);
        
        
}

void vStateHandleValue(){

    static unsigned char ucBufferIndex = 0;
    static unsigned char* ucBuffer[MAX_BUFFER_SIZE + 1];

    if(VALIDATED_INPUT(ucCommByte) && ucBufferIndex <= MAX_BUFFER_SIZE){
        ucBuffer[ucBufferIndex++] = ucCommByte;
        return;
    }

    else if(ucCommByte == ';'){
        ucBuffer[ucBufferIndex] = '\0';
        const float fTargetValue = fParserToFloat(ucBuffer);

        switch (xTargetParam)
        {
            case TEMPERATURE_TARGET:
                pSystemParameters->fTemperatureTarget = fTargetValue;
                break;

            case DUTY_CYCLE_HEATER:
                pSystemParameters->usDutyCycleHeater = (unsigned char)fTargetValue;
                break;
            
            case DUTY_CYCLE_COOLER:
                pSystemParameters->usDutyCycleCooler = (unsigned char)fTargetValue;
                break;

            case BUTTON_LOCK:
                pSystemParameters->usButtonLock = (unsigned char)fTargetValue;
                break;
            
            default:
                break;
        }

    }

    ucBufferIndex = 0;
    xCurrentState = IDLE;
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

        case VAL_SET:
            vStateHandleSet();
            break;

        case PARAM:
            vStateHandleParam();
            break;

        case VALUE:
            vStateHandleValue();
            break;

        default:
            break;
    }

    HAL_UART_Receive_IT(pUartPeripheral, &ucCommByte, 1);
}

void vCommunicationStateMachineInit(UART_HandleTypeDef* pHUart, SystemParameters* pSysParam){
    pUartPeripheral = pHUart;
    pSystemParameters = pSysParam;
    HAL_UART_Receive_IT(pUartPeripheral, &ucCommByte, 1);

}