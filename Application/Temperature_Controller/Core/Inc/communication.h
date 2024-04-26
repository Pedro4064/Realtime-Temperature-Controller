/*
 * communication.h
 *
 *  Created on: Apr 26, 2024
 *      Author: pedro
 */
#include "main.h"

#ifndef INC_COMMUNICATION_H_
#define INC_COMMUNICATION_H_


void vCommunicationInit(UART_HandleTypeDef* pUartModule, int iMessageMaxBufferSize, void (*pTransmissionMessageCallBack)(void), char* pMessage, char cMessageDelim);
void vCommunicationSend();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* pHUart);
#endif /* INC_COMMUNICATION_H_ */
