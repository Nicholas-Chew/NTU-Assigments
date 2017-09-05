#include "LinkedList.c"
#include "Queue.c"

////////////////////////////////////////////////////////////////////////////////

void recursiveReverse(Queue *q);

////////////////////////////////////////////////////////////////////////////////

int main(){

   Queue q;
 
   q.ll.head = NULL;
   q.ll.tail = NULL;
   q.ll.size = 0;

   enqueue(&q, 1);
   enqueue(&q, 2);
   enqueue(&q, 3);
   enqueue(&q, 4);
   enqueue(&q, 5);
   enqueue(&q, 6);
 
   printf("Queue: ");
   printList(&(q.ll));
   printf("\n");
   printf("Reversed queue: ");
   recursiveReverse(&q);

   while (!isEmptyQueue(&q))
      printf("%d ", dequeue(&q));
 
   return 0;
}

////////////////////////////////////////////////////////////////////////////////

void recursiveReverse(Queue *q)
{
   int i;
 
   if (isEmptyQueue(q))
      return;
   else {
      i = dequeue(q);
      recursiveReverse(q);
      enqueue(q, i);
   }
}



