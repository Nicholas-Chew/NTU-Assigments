#include <stdio.h>
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// These are for question 2. You should not change the prototypes of these functions
void sortedMergeLinkedList(LinkedList *ll1, LinkedList *ll2, LinkedList *resultMergedList);
int insertSortedLinkedList(LinkedList *ll, int item);

// You may use the following functions or you may write your own
void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2, resultMergedList;
	int c, i, j;

	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	//Initialize the merged linked list as an empty linked list
	resultMergedList.head = NULL;
	resultMergedList.size = 0;

	printf("1: Insert an integer to the sorted linked list 1:\n");
	printf("2: Insert an integer to the sorted linked list 2:\n");
	printf("3: Print sorted merged linked list:\n");
	printf("0: Quit:\n");
	printf("Please input your choice(1/2/3/0): ");
	scanf("%d", &c);

	while (c != 0)
	{
		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertSortedLinkedList(&ll1, i); // You need to code this function
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertSortedLinkedList(&ll2, i); // You need to code this function
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
			sortedMergeLinkedList(&ll1, &ll2, &resultMergedList); // You need to code this function
			printf("The resulting linked list is: ");
			printList(&resultMergedList);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			removeAllItems(&resultMergedList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////

void sortedMergeLinkedList(LinkedList *ll1, LinkedList *ll2, LinkedList *resultMergedList)
{
	// declare node to traverse through ll1 and 112
	ListNode *cur1, *cur2;
	cur1 = ll1->head;
	cur2 = ll2->head;

	//Remove all items in the result List for accurate result
	removeAllItems(resultMergedList);

	//Loop if there is still node to manipulate
	while(cur1!=NULL || cur2!=NULL)
	{
		// Insert using insertSortedLinkedList if ll1 still have value to traverse
		if(cur1 != NULL)
		{
			insertSortedLinkedList(resultMergedList,cur1->item);
			//Move to the next node;
			cur1 = cur1->next;
		}
		// Insert using insertSortedLinkedList if ll2 still have value to traverse
		if(cur2!=NULL)
		{
			insertSortedLinkedList(resultMergedList,cur2->item);
			//Move to the next node;
			cur2 = cur2->next;
		}
	}
}

int insertSortedLinkedList(LinkedList *ll, int item)
{
	//Index to keep track the position  
	int index = 0, result = 0;
	//Store the Currerent node to traverse list node
	ListNode *cur = ll->head; 

	//Check is the list empty
	while(cur!=NULL)
	{
		//If the list item(cur->item) is larger than the input item(item)
		//break the while loop and return the previous index to insert to the desinated positon.
		if(item < cur->item)
			break;
		//Index and cur are only increased after the condition checking.
		//Hence, previous value is store while checking.
		index ++;
		cur = cur->next;
	}

	result = insertNode(ll,index,item);
	return result==0 ? index:result; // If insert fail return -1, else index
}

//////////////////////////////////////////////////////////////////////////////////


void printList(LinkedList *ll)
{
	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

ListNode * findNode(LinkedList *ll, int index)
{
	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{
	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index)
{
	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}
	return -1;
}
