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
	
int hasGreatGrandchild(BTNode *node);

////////////////////////////////////////////////////////////////////////////////

int main()
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
 
   printf("\nusing root: \n");
   printf("Preorder: ");      print_preorder(root);        printf("\n");    
   printf("Inorder: ");       print_inorder(root);           printf("\n");
   printf("Postorder: ");     print_postorder(root);      printf("\n");
   	

   hasGreatGrandchild(root); 
   	
   printf("\n");


 // Create a tree for Q2: Tall enough so some nodes have great-grandchildren
 // Use array of BTNodes, create tree by linking nodes together
  /*
             0
        1         2
     3    4     5     6
    7 8 9  10 11 12 13 14 
   		 
 */
   for (i = 0; i <= 6; i++){
      btn[i].item = i;
      btn[i].left = &(btn[i*2 + 1]);
      btn[i].right = &(btn[i*2 + 2]);
   }
 
   for (i = 7; i <= 14; i++){
      btn[i].item = i;
      btn[i].left = NULL;
      btn[i].right = NULL;
   }
 
   root2 = &btn[0];
    	
		// using root2	  
   printf("\nusing root2: \n");
   printf("Preorder: ");       print_preorder(root2);        printf("\n");    
   printf("Inorder: ");      print_inorder(root2);           printf("\n");
   printf("Postorder: ");       print_postorder(root2);      printf("\n");
   
   hasGreatGrandchild(root2);
   
   return 0;
}

////////////////////////////////////////////////////////////////////////////////
int hasGreatGrandchild(BTNode *node)
{   
   int l, r;
 
 // Using postorder processing
 // Calculate the height of each node in the tree
 // Print out (data stored in) node that has height > n
 
   if (node == NULL)
      return -1;
 
   l = hasGreatGrandchild(node->left);
   r = hasGreatGrandchild(node->right);
 
   if (r > l)
      l = r;
   if (l >= 2)
      printf("node item: %d \n", node->item);
 
   //printf("node = %d level = %d\n", node->item, l);
   return (l + 1);
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
