#include "main.h"

#define CIRCULAR_INDEX_INCREMENT(x, max_number) (x+1)%max_number

static void (*pMessageCallBack)(void);
static int iMessageBufferSize;
static unsigned char* pMessageBuffer;
static char cMessageDelimiter;
static UART_HandleTypeDef* pUartPeripheral;

void vCommunicationInit(UART_HandleTypeDef* pUartModule, int iMessageMaxBufferSize, void (*pTransmissionMessageCallBack)(void), unsigned char* pMessage, char cMessageDelim){
    iMessageBufferSize = iMessageMaxBufferSize;
    pMessageCallBack = pTransmissionMessageCallBack;
    pMessageBuffer = pMessage;
    cMessageDelimiter = cMessageDelim;
    pUartPeripheral = pUartModule;

    HAL_UART_Receive_IT(pUartPeripheral, pMessageBuffer, 1);
}

void vCommunicationSend(){}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef* pHUart){
    static int iCurrentBufferPosition = 0;

    if(pHUart != pUartPeripheral)
        return;

    char cTransmittedData = pMessageBuffer[iCurrentBufferPosition];
    iCurrentBufferPosition = CIRCULAR_INDEX_INCREMENT(iCurrentBufferPosition, iMessageBufferSize);

    if(cTransmittedData == cMessageDelimiter){
        (*pMessageCallBack)();
        iCurrentBufferPosition = 0;
    }

    HAL_UART_Receive_IT(pUartPeripheral, pMessageBuffer+iCurrentBufferPosition, 1);
    
}

