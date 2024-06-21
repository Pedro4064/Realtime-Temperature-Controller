 // **********************************************//
// File name:        queue.h                     //
// File description: This file defines           //
//                   a queue system              //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 21/Jun/2024                 //
// Revision date:    21/Jun/2024                 //
// **********************************************//



#ifndef H_QUEUE_INC_
#define H_QUEUE_INC_

typedef struct QUEUE{
    char cQ[10];
    int iTop;
    int iBottom;
    int iSize;
} queue;


// ********************************************************** //
// Method name:        vQueueInsert                           //
// Method description: Insert element in Queue                //
// Input params:       pQ                                     //
//                        Pointer  to the queue to insert the //
//                        value                               //
//                     cValue                                 //
//                        Value to be inserted into the queue //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vQueueInsert(queue* pQ, char cValue);

// ********************************************************** //
// Method name:        cQueueGet                              //
// Method description: Get the first element in the Queue     //
// Input params:       pQ                                     //
//                        Pointer to the queue                //
// Output params:      char                                   //
//                        First value in the queue (FIFO)     //
// ********************************************************** //
char cQueueGet(queue* pQ);

// ********************************************************** //
// Method name:        cQueueIsEmpty                          //
// Method description: Check if queue is empty                //
// Input params:       pQ                                     //
//                        Pointer to the queue                //
// Output params:      char                                   //
//                        Boolean  value,  1  if  is  empty 0 //
//                        otherwise                           //
// ********************************************************** //
char cQueueIsEmpty(queue* pQ);

// ********************************************************** //
// Method name:        vQueueClear                            //
// Method description: Clear the queue                        //
// Input params:       pQ                                     //
//                        Pointer to the queue to be cleared  //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void vQueueClear(queue* pQ);
#endif