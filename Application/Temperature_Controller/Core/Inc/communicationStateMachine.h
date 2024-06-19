// **********************************************//
// File name:        communicationStateMachine.h //
// File description: This file declare functions //
//                   interface and data types for//
//                   communicationStateMachine.  //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 26/Abr/2024                 //
// Revision date:    29/Abr/2024                 //
// **********************************************//

#ifndef INC_COMMUNICATIONSTATEMACHINE_H_
#define INC_COMMUNICATIONSTATEMACHINE_H_

// ********************************************************** //
// Method name:        vCommunicationStateMachineInit         //
// Method description: This    function   initialize   UART   //
//                     communication library.                 //
// Input params:       pHUart                                 //
//                        Pointer  to  UART  peripheral to be //
//                        used.                               //
//                     xSysParam                              //
//                        Variable  containing the parameters //
//                        that can be assigned or returnedvia //
//                        UART communication.                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vCommunicationStateMachineInit(UART_HandleTypeDef* pHUart, applicationParameters* xSysParam);

// ************************************************************* //
// Method name:        vCommunicationStateMachineHandleStateReady//
// Method description: This  function handles the 'Ready'        //
//                     state    of   the   state   machine,      //
//                     determining  the next state based on      //
//                     the received byte.                        //
// Input params:       void                                      //
//                        N/A                                    //
// Output params:      void                                      //
//                        N/A                                    //
// ************************************************************* //
void vCommunicationStateMachineHandleStateReady();

// *********************************************************** //
// Method name:        vCommunicationStateMachineHandleStateGet//
// Method description: A  function  that  handles the 'Get'    //
//                     state    of   the   state   machine,    //
//                     determining  the next state based on    //
//                     the received byte.                      //
// Input params:       void                                    //
//                        N/A                                  //
// Output params:      void                                    //
//                        N/A                                  //
// *********************************************************** //
void vCommunicationStateMachineHandleStateGet();

// *********************************************************** //
// Method name:        vCommunicationStateMachineHandleStateSet//
// Method description: A  function  that  handles the 'Set'    //
//                     state    of   the   state   machine,    //
//                     determining  the next state based on    //
//                     the received byte.                      //
// Input params:       void                                    //
//                        N/A                                  //
// Output params:      void                                    //
//                        N/A                                  //
// *********************************************************** //
void vCommunicationStateMachineHandleStateSet();

// ************************************************************* //
// Method name:        vCommunicationStateMachineHandleStateParam//
// Method description: A  function that handles the 'Param'      //
//                     state    of   the   state   machine,      //
//                     determining  the next state based on      //
//                     the received byte.                        //
// Input params:       void                                      //
//                        N/A                                    //
// Output params:      void                                      //
//                        N/A                                    //
// ************************************************************* //
void vCommunicationStateMachineHandleStateParam();

// ************************************************************* //
// Method name:        vCommunicationStateMachineHandleStateValue//
// Method description: A  function that handles the 'Value'      //
//                     state    of   the   state   machine,      //
//                     determining  the next state based on      //
//                     the received byte.                        //
// Input params:       void                                      //
//                        N/A                                    //
// Output params:      void                                      //
//                        N/A                                    //
// ************************************************************* //
void vCommunicationStateMachineHandleStateValue();

// ********************************************************** //
// Method name:        vCommunicationStateMachineProcessByte  //
// Method description: This     function    implements    a   //
//                     byte-by-byte  state machine for UART   //
//                     communication                          //
// Input params:       void                                   //
//                        N/A                                 //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vCommunicationStateMachineProcessByte();

#endif /* INC_COMMUNICATIONSTATEMACHINE_H_ */
