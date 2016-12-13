/**
*		@file LinkedList.h
*		@brief Provides a linked list implementation
*	
*		@author		Tim Rollet
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdlib.h>
/** Linked list node container.
*	Should be used internally to LinkedList only.
*/
typedef struct LinkedListNode_s {
	struct LinkedListNode_s * head;		/**< element before this node in the list */
	struct LinkedListNode_s * tail;		/**< element after this node in the list */
	void* data;							/**< data contained within the node */
} LinkedListNode;

/**	Linked list that stores arbitrary data.
*	Use accessor methods only.
*/
typedef struct LinkedList_s {
	LinkedListNode* head;				/**< first element of the list */
	LinkedListNode* tail;				/**< last element of the list */
	int size;							/**< total number of elements in the list */
} LinkedList;


/** Create an empty linked list.
Returns a pointer to a new malloced list.
*/
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

/**
*	@brief	Run a function on every element and update the list.
*	@param	list	the list to map
*	@param	func	the function to run on every element
*/
void linked_list_map(LinkedList* list, void* (*) (void*) func);

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
