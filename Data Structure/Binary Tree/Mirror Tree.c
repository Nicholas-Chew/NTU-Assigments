#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////

typedef struct _btnode{
   int item;
   struct _btnode *left;
   struct _btnode *right;
} BTNode;

////////////////////////////////////////////////////////////////////////////////

void print_preorder(BTNode *cur);
void print_inorder(BTNode *cur);
void print_postorder(BTNode *cur);
	
void mirrorTree(BTNode *node);

////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[])
{
   int i;
   BTNode *root, *root2;
   BTNode btn[15];
 
 // Create the tree in Q1
 // Using manual dynamic allocation of memory for BTNodes
 /*
            4
      5          2
   	  6      3   1
   	7	 
 */
   root = malloc(sizeof(BTNode));
   root->item = 4;
 
   root->left = malloc(sizeof(BTNode));
   root->left->item = 5;
 
   root->right = malloc(sizeof(BTNode));
   root->right->item = 2;
 
   root->left->left = NULL;
 
   root->left->right = malloc(sizeof(BTNode));
   root->left->right->item = 6;
 
   root->left->right->right = NULL;
 
   root->left->right->left = malloc(sizeof(BTNode));
   root->left->right->left->item = 7;
 
   root->left->right->left->left = NULL;
   root->left->right->left->right = NULL;

   root->right->left = malloc(sizeof(BTNode));
   root->right->left->item = 3;
 
   root->right->right = malloc(sizeof(BTNode));
   root->right->right->item = 1;

   root->right->left->left = NULL;
   root->right->left->right = NULL;
 
   root->right->right->left = NULL;
   root->right->right->right = NULL;
 
   printf("Preorder: ");       print_preorder(root);        printf("\n");    
   printf("Inorder: ");      print_inorder(root);           printf("\n");
   printf("Postorder: ");       print_postorder(root);      printf("\n");
   	
   mirrorTree(root);
   
/*after mirror()
            4
      2          5
   1     3     6  
   	           7	 
 */	
   printf("\nAfter mirror():\n");
   printf("Preorder: ");       print_preorder(root);        printf("\n");    
   printf("Inorder: ");      print_inorder(root);           printf("\n");
   printf("Postorder: ");       print_postorder(root);      printf("\n");

   return 0;
}

////////////////////////////////////////////////////////////////////////////////
void mirrorTree(BTNode *node)
{
   BTNode *temp;
 
   if (node == NULL)
      return;
 
 // Swap left and right BTNode pointers

 // Using pre-order processing
   temp = node->left;
   node->left = node->right;
   node->right = temp;
   mirrorTree(node->left);
   mirrorTree(node->right);

 // Using post-order processing
/* 
   mirrorTree(node->left);
   mirrorTree(node->right);
   temp = node->left;
   node->left = node->right;
   node->right = temp;
  */

 // What about using in-order processing?
 /*
   mirrorTree(node->left);
   temp = node->left;
   node->left = node->right;
   node->right = temp;
   mirrorTree(node->left);
  */
}


////////////////////////////////////////////////////////////////////////////////
void print_preorder(BTNode *cur){
   if (cur == NULL)
      return;  
   printf("%d ", cur->item);
   print_preorder(cur->left);
   print_preorder(cur->right);
}
	
void print_inorder(BTNode *cur){
   if (cur == NULL)
      return;
   print_inorder(cur->left);
   printf("%d ", cur->item);
   print_inorder(cur->right);
}
	
void print_postorder(BTNode *cur){
   if (cur == NULL)
      return;
   print_postorder(cur->left);
   print_postorder(cur->right);
   printf("%d ", cur->item);
}
