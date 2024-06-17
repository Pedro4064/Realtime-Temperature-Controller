#ifndef H_QUEUE_INC_
#define H_QUEUE_INC_

typedef struct QUEUE{
    char cQ[10];
    int iTop;
    int iBottom;
    int iSize;
} queue;


void vQueueInsert(queue* pQ, char cValue);

char cQueueGet(queue* pQ);

char cQueueIsEmpty(queue* pQ);

void vQueueClear(queue* pQ);
#endif