// **********************************************//
// File name:        communicationStateMachine.c //
// File description: This file implements the    //
//                   state machine communication //
//                   to set or get parameters    //
//                   such as temperature target, //
//                   velocyty of cooler and      //
//                   others                      //   
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 26/Abr/2024                 //
// Revision date:    29/Abr/2024                 //
// **********************************************//

#include <main.h>
#include "parser.h"
#include "application.h"

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

#define VALIDATED_INPUT(x) ((x >= '0' && x <= '9') || x == ',')
#define MAX_BUFFER_SIZE 7

static State xCurrentState = IDLE;
static ParamID xTargetParam;
static UART_HandleTypeDef* pUartPeripheral;
static unsigned char ucCommByte;
static applicationParameters* pSystemParameters;

void vCommunicationStateMachineStateHandleReady(){
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

void vCommunicationStateMachineStateHandleGet(){
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

void vCommunicationStateMachineStateHandleSet(){
    
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

void vCommunicationStateMachineStateHandleParam(){
    xCurrentState = IDLE;
    if(ucCommByte != ';')
        return;

    static char message[11];
    float fTargetValue;

    switch (xTargetParam)
    {
    case TEMPERATURE_CURRENT:
        fTargetValue = (*pSystemParameters).tempMgtCtl.fTemperatureCurrent;
        break;

    case VELOCITY_COOLER:
        fTargetValue = (float)(*pSystemParameters).tempMgtCtl.uiVelocityCooler;
        break;
    
    default:
        return;
        break;
    }

    vParserFloatToString(&message, fTargetValue);
    HAL_UART_Transmit_IT(pUartPeripheral, message, 11);
        
        
}

void vCommunicationStateMachineStateHandleValue(){

    static unsigned char ucBufferIndex = 0;
    static unsigned char ucBuffer[MAX_BUFFER_SIZE + 1];

    if(VALIDATED_INPUT(ucCommByte) && ucBufferIndex <= MAX_BUFFER_SIZE){
        ucBuffer[ucBufferIndex++] = ucCommByte;
        return;
    }

    else if(ucCommByte == ';'){
        ucBuffer[ucBufferIndex] = '\0';
        const float fTargetValue = fParserToFloat(ucBuffer, MAX_BUFFER_SIZE + 1);

        switch (xTargetParam)
        {
            case TEMPERATURE_TARGET:
                pSystemParameters->tempMgtCtl.fTemperatureTarget = fTargetValue;
                break;

            case DUTY_CYCLE_HEATER:
                pSystemParameters->tempMgtCtl.fDutyCycleHeater = fTargetValue;
                break;
            
            case DUTY_CYCLE_COOLER:
                pSystemParameters->tempMgtCtl.fDutyCycleCooler = fTargetValue;
                break;

            default:
                break;
        }

    }

    ucBufferIndex = 0;
    xCurrentState = IDLE;
}

void vCommunicationStateMachineProcessByte(){

    HAL_UART_Receive_IT(pUartPeripheral, &ucCommByte, 1);
    if(ucCommByte == '#'){
        xCurrentState = READY;
        return;
    }

    switch (xCurrentState)
    {
        case IDLE:
            return;
        
        case READY:
            vCommunicationStateMachineStateHandleReady();
            break;

        case GET:
            vCommunicationStateMachineStateHandleGet();
            break;

        case VAL_SET:
            vCommunicationStateMachineStateHandleSet();
            break;

        case PARAM:
            vCommunicationStateMachineStateHandleParam();
            break;

        case VALUE:
            vCommunicationStateMachineStateHandleValue();
            break;

        default:
            break;
    }

}

void vCommunicationStateMachineInit(UART_HandleTypeDef* pHUart, applicationParameters* pSysParam){
    pUartPeripheral = pHUart;
    pSystemParameters = pSysParam;
    HAL_UART_Receive_IT(pUartPeripheral, &ucCommByte, 1);

}
