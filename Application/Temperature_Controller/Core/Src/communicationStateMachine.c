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
    // Param ID
    TEMPERATURE_CURRENT = 't',  // Get Value
    VELOCITY_COOLER = 'v',      // Get Value
    TEMPERATURE_TARGET = 't',   // Set Value
    BUZZER_PLAY = 'b',          // Set Value
    BUZZER_FREQ = 'f',          // Set And Get Value
    BUZZER_PERI = 'T',          // Set And Get Value
    PID_KP = 'p',               // Set And Get Value
    PID_KI = 'i',               // Set And Get Value
    PID_KD = 'd',               // Set And Get Value 

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
    case BUZZER_FREQ:
    case BUZZER_PERI:
    case PID_KP:
    case PID_KI:
    case PID_KD:

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
        case BUZZER_PLAY:
        case BUZZER_FREQ:
        case BUZZER_PERI:
        case PID_KP:
        case PID_KI:
        case PID_KD:

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

    static unsigned char ucMessage[11];
    float fTargetValue;

    switch (xTargetParam)
    {
    case TEMPERATURE_CURRENT:
        fTargetValue = (*pSystemParameters).tempMgtCtl.fTemperatureCurrent;
        break;

    case VELOCITY_COOLER:
        fTargetValue = (float)(*pSystemParameters).tempMgtCtl.uiVelocityCooler;
        break;

    case BUZZER_FREQ:
        fTargetValue = (float)(pSystemParameters->buzzerInterface.usFrequency);
        break;

    case BUZZER_PERI:
        fTargetValue = (float)(pSystemParameters->buzzerInterface.usPeriod);
        break;

    case PID_KP:
        fTargetValue = pSystemParameters->tempMgtCtl.fKp;
        break;

    case PID_KI:
        fTargetValue = pSystemParameters->tempMgtCtl.fKi;
        break;

    case PID_KD:
        fTargetValue = pSystemParameters->tempMgtCtl.fKd;
        break;
    
    default:
        return;
        break;
    }

    vParserFloatToString(ucMessage, fTargetValue);
    HAL_UART_Transmit_IT(pUartPeripheral, ucMessage, 11);
        
        
}

void vCommunicationStateMachineStateHandleValue(){

    static unsigned char ucBufferIndex = 0;
    static unsigned char ucBuffer[MAX_BUFFER_SIZE + 1];
    char cSaveSuccessful;

    if(VALIDATED_INPUT(ucCommByte) && ucBufferIndex < MAX_BUFFER_SIZE){
        ucBuffer[ucBufferIndex++] = ucCommByte;
        return;
    }

    else if(ucCommByte == ';'){
        ucBuffer[ucBufferIndex] = '\0';
        const float fTargetValue = fParserToFloat(ucBuffer, MAX_BUFFER_SIZE + 1);

        switch (xTargetParam)
        {
            case TEMPERATURE_TARGET:
                if(fTargetValue > 90){
                    HAL_UART_Transmit_IT(pUartPeripheral, (unsigned char*)"[CONFIG SYS] ERROR: Max Value Exceeded\n\r",  42);
                    cSaveSuccessful = 0;
                    break;
                }
                pSystemParameters->tempMgtCtl.fTemperatureTarget = fTargetValue;
                cSaveSuccessful = 1;
                break;

            case BUZZER_PLAY:
                if(fTargetValue != 1){
                    HAL_UART_Transmit_IT(pUartPeripheral, (unsigned char*)"[CONFIG SYS] ERROR: Val. Outside Range\n\r",  42);
                    cSaveSuccessful = 0;
                    break;
                }
                pSystemParameters->buzzerInterface.cPlay = (char)fTargetValue;
                cSaveSuccessful = 1;
                break;

            case BUZZER_FREQ:
                pSystemParameters->buzzerInterface.usFrequency = (unsigned short)fTargetValue;
                pSystemParameters->buzzerInterface.cBuzzerConfigChanged = 1;
                cSaveSuccessful = 1;
                break;

            case BUZZER_PERI:
                pSystemParameters->buzzerInterface.usPeriod = (unsigned short)fTargetValue;
                pSystemParameters->buzzerInterface.cBuzzerConfigChanged = 1;
                cSaveSuccessful = 1;
                break;

            case PID_KP:
                if(fTargetValue < 0 || fTargetValue >= 100){
                    HAL_UART_Transmit_IT(pUartPeripheral, (unsigned char*)"[CONFIG SYS] ERROR: Val. Outside Range\n\r",  42);
                    cSaveSuccessful = 0;
                    break;
                }
                pSystemParameters->tempMgtCtl.fKp = fTargetValue;
                pSystemParameters->tempMgtCtl.cPidConfigChanged = 1;
                cSaveSuccessful = 1;
                break;
            
            case PID_KI:
                if(fTargetValue < 0 || fTargetValue >= 100){
                    HAL_UART_Transmit_IT(pUartPeripheral, (unsigned char*)"[CONFIG SYS] ERROR: Val. Outside Range\n\r",  42);
                    cSaveSuccessful = 0;
                    break;
                }
                pSystemParameters->tempMgtCtl.fKi = fTargetValue;
                pSystemParameters->tempMgtCtl.cPidConfigChanged = 1;
                cSaveSuccessful = 1;
                break;
            
            case PID_KD:
                if(fTargetValue < 0 || fTargetValue >= 100){
                    HAL_UART_Transmit_IT(pUartPeripheral, (unsigned char*)"[CONFIG SYS] ERROR: Val. Outside Range\n\r",  42);
                    cSaveSuccessful = 0;
                    break;
                }
                pSystemParameters->tempMgtCtl.fKd = fTargetValue;
                pSystemParameters->tempMgtCtl.cPidConfigChanged = 1;
                cSaveSuccessful = 1;
                break;
            

            default:
                break;

        }

        if(cSaveSuccessful){
            HAL_UART_Transmit_IT(pUartPeripheral, (unsigned char*)"[CONFIG SYS] Value set SUCCESSFUL\n\r",  35);
            pSystemParameters->buzzerInterface.cPlay = 1;
            cSaveSuccessful = 0;
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
