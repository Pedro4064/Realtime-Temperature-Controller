/*
 * communication.h
 *
 *  Created on: Apr 26, 2024
 *      Author: pedro
 */
#include "main.h"

#ifndef INC_COMMUNICATION_H_
#define INC_COMMUNICATION_H_

// ********************************************************** //
// Method name:        vCommunicationInit                     //
// Method description: Initialize UART communication library  //
// Input params:       pUartModule                            //
//                        Pointer  to  UART  peripheral to be //
//                        used                                //
//                     iMessageMaxBufferSize                  //
//                        Max  number  of  the  elements of a //
//                        message                             //
//                     pTransmissionMessageCallBack           //
//                        Pointer  to callback function to be //
//                        called at the end of message receive//
//                     pMessage                               //
//                        Pointer to message buffer           //
//                     cMessageDelim                          //
//                        Delimiter character to determineend //
//                        of message                          //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vCommunicationInit(UART_HandleTypeDef* pUartModule, int iMessageMaxBufferSize, void (*pTransmissionMessageCallBack)(void), char* pMessage, char cMessageDelim);

// ********************************************************** //
// Method name:        vCommunicationSend                     //
// Method description: Send messages                          //
// Input params:       void                                   //
//                        N/A                                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vCommunicationSend();

// ********************************************************** //
// Method name:        HAL_UART_RxCpltCallback                //
// Method description: UART package receive callback          //
// Input params:       pHUart                                 //
//                        Pointer    to    UART    peripheral //
//                        responsible for callback call       //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* pHUart);
#endif /* INC_COMMUNICATION_H_ */
