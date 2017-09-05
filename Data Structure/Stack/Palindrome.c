#include <ctype.h>
#include "LinkedList.c"
#include "Stack.c"
#include "Queue.c"

////////////////////////////////////////////////////////////////////////////////

void palindrome(char *word);

////////////////////////////////////////////////////////////////////////////////

int main()
{
   char str[80];

   printf("Enter a sentence (e.g. A man a plan a canal Panama): ");
   gets(str);
   palindrome(str);

   return 0;
}

////////////////////////////////////////////////////////////////////////////////

void palindrome(char *word)
{
   int i;
   Stack s;
   Queue q;
	
   s.ll.head = NULL;
   s.ll.tail = NULL;
   s.ll.size = 0;
   q.ll.head = NULL;
   q.ll.tail = NULL;
   q.ll.size = 0;
 
 // Put the whole string in a stack and a queue, stripping out spaces
 // Pop first half of stripped string off the stack letter by letter, 
 // comparing with second half

   printf("The input string is: %s\n", word);   
   while (*word != '\0'){
      if (*word != ' '){
         push(&s, toupper(*word));
         enqueue(&q, toupper(*word));
      }
      word++;
   }

 // Integer division by 2, ignores the middle character in an odd-length string
   i = s.ll.size / 2;
   while (i > 0) {
      if (pop(&s) != dequeue(&q)){
         printf("The string is not a palindrome\n");
         return;
      }
      i--;
   }
 
   printf("The string is a palindrome\n");
}

