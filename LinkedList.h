#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdlib.h>
/**
* Provides a Linked List implementation.  LinkedListNode should not be used by other files.
* Justification for use: it is very easy and fast to append and resize linked lists.
* Loot lists will routinely be appended to the player's inventories, so this is ideal.
**/
typedef struct LinkedListNode_s {
	struct LinkedListNode_s * head;
	struct LinkedListNode_s * tail;
	void* data;
} LinkedListNode;

typedef struct LinkedList_s {
	LinkedListNode* head;
	LinkedListNode* tail;
	int size;
} LinkedList;


//creates an empty list
LinkedList* linked_list_create();

//creates an empty node
LinkedListNode* linked_list_node_create();

//add a datum to the end of a linked list
void linked_list_add(LinkedList* list, void* data);

//non-destructively return the indexed element from the list 
//returns null if index out of range
void* linked_list_get(LinkedList* list, int index);

//appends two linked lists to each other, and frees list b
void linked_list_append(LinkedList* a, LinkedList* b);

//Search for a target with a provided compare function.
//Function should take same type as list->head->data for first argument and same type as target for second
void* linked_list_search(LinkedList* list, void* target, int (*cmp)(const void*,const void*));

//removes an element from a linked list and returns it
void* linked_list_remove(LinkedList* list, int index);

//free a list and all of its nodes
//does NOT free node data. it is up to the user to handle freeing node data!
void linked_list_free(LinkedList* list);

//free a list, all of its nodes, and naively free data
//If your data is more complicated than a single malloc, you need to deal w/ it yourself
void linked_list_free_and_data_naive(LinkedList* list);

//Free a list, all of its nodes, and free data with provided function
void linked_list_free_and_data(LinkedList* list, void (*data_free)(void*));

#endif