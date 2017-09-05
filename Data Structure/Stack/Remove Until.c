#include "LinkedList.c"
#include "Stack.c"

void removeUntil(Stack *s, int value);

////////////////////////////////////////////////////////////////////////////////

int main(){
 
   Stack s;
   int value;
	
   s.ll.head = NULL;
   s.ll.tail = NULL;
   s.ll.size = 0;
 
   printf("Stack: ");   
   push(&s, 1);
   push(&s, 2);
   push(&s, 3);
   push(&s, 4);
   push(&s, 5);
   push(&s, 6);
   push(&s, 5);
   push(&s, 4);
   push(&s, 3);
   push(&s, 2);
   push(&s, 1);

   printList(&(s.ll));
   printf("\n");
   printf("Enter the value for removeUntil(): ");
   scanf("%d", &value);
   removeUntil(&s, value);
 
   printf("Remaining stack is: ");
   while (!isEmptyStack(&s))
      printf("%d ", pop(&s));
 
   return 0;
}

////////////////////////////////////////////////////////////////////////////////

void removeUntil(Stack *s, int value)
{
   while (!isEmptyStack(s)){
      if (peek(s) != value)
         pop(s);
      else
         break;
   }
}

