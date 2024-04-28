/*
 * communicationStateMachine.h
 *
 *  Created on: Apr 27, 2024
 *      Author: ES670 B
 */

#ifndef INC_COMMUNICATIONSTATEMACHINE_H_
#define INC_COMMUNICATIONSTATEMACHINE_H_


void vCommunicationStateMachineInit(UART_HandleTypeDef* pHUart, SystemParameters* xSysParam);
void vCommunicationStateMachineProcessByte();

#endif /* INC_COMMUNICATIONSTATEMACHINE_H_ */
