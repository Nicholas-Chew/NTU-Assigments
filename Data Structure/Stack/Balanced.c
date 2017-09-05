#include <string.h>
#include "LinkedList.c"
#include "Stack.c"

////////////////////////////////////////////////////////////////////////////////

void balanced(char *expression);

////////////////////////////////////////////////////////////////////////////////

int main()
{
   char str[80];
   int status=1;

   while (status) {
      printf("Enter an expression (-1 to exit): ");
      gets(str);
      status = strcmp(str, "-1");
      if (status)
         balanced(str);
   }
/*
 balanced("([{{}[]}])");
 balanced("()");
 balanced("");
 balanced("]");
 balanced("{");
 balanced("[[[[[[[[[[[[[[[[[)))))))))");
 balanced("{{{]]]]]]]]]]]]]]]]]]]]");
*/
 
   return 0;
}

////////////////////////////////////////////////////////////////////////////////

void balanced(char *expression)
{

   Stack s;
   s.ll.head = NULL;
   s.ll.tail = NULL;
   s.ll.size = 0;
 
 // Check one character at a time
 // If we see an opening bracket, store it in a stack
 // If we see a closing bracket, check stack for matching opening bracket (should be on top)
 // The moment we see a mismatch, expression is not balanced, return
 // If we finish looking at the expression and the stack is empty, it's balanced
 
   printf("%s\n", expression);
 
   while (*expression){
      if (*expression == '(' || *expression == '[' || *expression == '{'){
         push(&s, *expression);
      }
      else if (*expression == ')'){
         if (isEmptyStack(&s) || pop(&s) != '('){
            printf("The expression is not balanced\n");
            return;
         }
      }
      else if (*expression == ']'){
         if (isEmptyStack(&s) || pop(&s) != '['){
            printf("The expression is not balanced\n");
            return;
         }
      }
      else if (*expression == '}'){
         if (isEmptyStack(&s) || pop(&s) != '{'){
            printf("The expression is not balanced\n");
            return;
         }
      }
      expression++;
   }
 
   if (isEmptyStack(&s))
      printf("The expression is balanced\n");
   else
      printf("The expression is not balanced\n");

}

