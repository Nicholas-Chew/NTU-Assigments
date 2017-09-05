#ifndef Queue_h
#define Queue_h

#include "LinkedList.h"

////////////////////////////////////////////////////////////////////////////////

typedef struct _queue{
   LinkedList ll;
} Queue;

////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *s);

#endif