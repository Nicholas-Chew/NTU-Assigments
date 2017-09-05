#include <stdio.h> 
#include <stdlib.h> 

//////////////////////////////////////////////////////////////////// 
//////////// 

typedef struct _btnode{ 
   int item; 
   struct _btnode *left; 
   struct _btnode *right; 

} BTNode; 

//////////////////////////////////////////////////////////////////// 
//////////// 

int smallestValue(BTNode *node); 

void print_preorder(BTNode *cur);
void print_inorder(BTNode *cur);
void print_postorder(BTNode *cur);

//////////////////////////////////////////////////////////////////// 

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

	//question 3
   printf("The smallest value in the tree: %d\n", smallestValue(root));
	
   return 0; 
} 
//////////////////////////////////////////////////////////////////
int smallestValue(BTNode *node) 
{ 
   /* using postorder processing */
   
   int l,r;
    
   if (node==NULL) 
      return 100000; 

   l=smallestValue(node->left); 
   r=smallestValue(node->right); 
   
   if (l < node->item && l < r) 
      return l; 
   else if (r < node->item && r < l) 
      return r; 
   else
      return node->item; 
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
