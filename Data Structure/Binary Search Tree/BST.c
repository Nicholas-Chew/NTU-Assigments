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

void insertBSTNode(BTNode **node, int value);
void printBSTInOrder(BTNode *node);
int isBST(BTNode *node, int min, int max);

////////////////////////////////////////////////////////////////////
////////////
int main(){
   int i=0;

   BTNode *root=NULL;

	//question 1
   do{
      printf("input a value you want to insert(-1 to quit):");
   	
      scanf("%d",&i);
      if (i!=-1) 
         insertBSTNode(&root,i);
   }while(i!=-1);	

	//question 2
   printf("\n");
   printf("printBSTInOrder: ");
   printBSTInOrder(root);
   printf("\n");
   
	//question 3
   if ( isBST(root,-1000000, 1000000)==1 )
      printf("It is a BST!\n");
   else
      printf("It is not a BST!\n");

	/*
	i=root->item ;
	root->item =root->left->item;
	root->left->item =i;

	if ( isBST(root,-1000000, 1000000)==1)
		printf("It is a BST!\n");
	else
		printf("It is not a BST!\n");
	*/


   return 0;
}

//////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value)
{
   if (*node==NULL) //if the tree is empty
   {
      *node=malloc(sizeof(BTNode));
      (*node)->item =value;
      (*node)->left =NULL;
      (*node)->right = NULL;
      return;
   }
   if ((*node)->item > value) //value is smaller than the node
      insertBSTNode(&((*node)->left), value);
   else if ((*node)->item <value) //value is larger than the node
      insertBSTNode(&((*node)->right), value);
   else // (*node)->item == value, value will not be inserted
   {
      printf("%d already exists in the BST\n");
      return;
   }
   return;
}

//////////////////////////////////////////////////////////////
void printBSTInOrder(BTNode *node)
{
   if (node==NULL)
      return;

   printBSTInOrder(node->left );
   printf("%d, ", node->item);
   printBSTInOrder(node->right);

   return;
}

/////////////////////////////////////////////////////////////////

int isBST(BTNode *node, int min, int max) // the item stored in node has to be smaller than max and larger than min
{
   if (node==NULL) 
      return 1;
	
   if (node->item >= max || node->item <= min) //the node's value should belong   
                                                       // to (min, max). 
      return 0;

	// its left node should be smaller than node->item
	// its right node should be larger than node->item
   return isBST(node->left, min, node->item)&& isBST(node->right, node->item, max) ; 	
}


