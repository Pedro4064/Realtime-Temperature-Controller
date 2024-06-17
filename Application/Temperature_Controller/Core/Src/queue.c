#include "queue.h"

#define BUFFER_SIZE 10
#define CIRCULAR_INCREMENT(x) (x+1)%BUFFER_SIZE
#define CIRCULAR_DECREMENT(x) ((x - 1) < 0)? (BUFFER_SIZE - 1):x-1
#define ELEMENT_COUNTER_INCREMENT(x) (x+1) > BUFFER_SIZE? BUFFER_SIZE:x+1
#define ELEMENT_COUNTER_DECREMENT(x) (x-1) < 0? 0:x-1

void vQueueInsert(queue* pQ, char cValue){
    
    // If the queue is empty, do not increment iBottom and iTop, since the first element 
    //is being inserted the top and bottom elements are the same, and incrementing
    //would cause an error in the cQueueGet logic
    pQ->iBottom = cQueueIsEmpty(pQ) ?  pQ->iBottom:CIRCULAR_INCREMENT(pQ->iBottom) ;
    pQ->iTop = (pQ->iBottom == pQ->iTop && !cQueueIsEmpty(pQ)) ? CIRCULAR_INCREMENT(pQ->iTop): pQ->iTop;

    pQ->cQ[pQ->iBottom] = cValue;

    
    pQ->iSize = ELEMENT_COUNTER_INCREMENT(pQ->iSize);
}

char cQueueGet(queue* pQ){

    // If deQueue operation is done on an empty queue, return zero
    if(cQueueIsEmpty(pQ))
        return 0;

    // Decrement the element counter to account for the element being removed
    pQ->iSize = ELEMENT_COUNTER_DECREMENT(pQ->iSize);

    // If There are no more elements, there is no need to increment the Top Counter,
    //since doing so would cause a mismatch between the Top and Bottom indexes and
    //would result in an error on the vQueueInsert logic
    char cReturnValue = pQ->cQ[pQ->iTop];
    pQ->iTop = cQueueIsEmpty(pQ) ? pQ-> iTop : CIRCULAR_INCREMENT(pQ->iTop);
    
    return cReturnValue;
}

char cQueueIsEmpty(queue* pQ){
    return pQ->iSize == 0;
}

void vQueueClear(queue* pQ){
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        pQ->cQ[i] = '\0';
    }
    
}