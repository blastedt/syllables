#include <string.h>
#include <stdio.h>

#include "LinkedList.h"

/**
* Create a new linked list and return a pointer to it.
**/
LinkedList* linked_list_create() {
	LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}

//Make a new linked list node
LinkedListNode* linked_list_node_create() {
	LinkedListNode* node = (LinkedListNode*) malloc(sizeof(LinkedListNode));
	node->head = NULL;
	node->tail = NULL;
	node->data = NULL;
	return node;
}

/**
* Add an element to a linked list.
**/
void linked_list_add(LinkedList* list, void* data) {
	LinkedListNode* new_node = linked_list_node_create();
	new_node->data = data;
	LinkedListNode* old_tail = list->tail;
	list->tail = new_node;
	if (list->size > 0) {
		old_tail->tail = new_node;
		new_node->head = old_tail;
	}  else {
		//size = 0
		list->head = new_node;
	}
	list->size = list->size + 1;
}

//Get the element at index
void* linked_list_get(LinkedList* list, int index) {
	if (index >= list->size || index < 0) {
		return NULL; //element not found
	}
	LinkedListNode* cur_node;
	if (index < list->size/2) {
		//first half of the list, so iterate forwards
		cur_node = list->head;
		while (index > 0) {
			cur_node = cur_node->tail;
			index--;
		}
	} else {
		//more than halfway along, so iterate backwards
		cur_node = list->tail;
		index = list->size - 1 - index;	//transform the index into distance from tail
		while (index > 0) {
			cur_node = cur_node->head;
			index--;
		}
	}
	return cur_node->data;

}

//append two linked lists
void linked_list_append(LinkedList* a, LinkedList* b) {
	LinkedListNode* atail = a->tail;
	LinkedListNode* bhead = b->head;
	LinkedListNode* btail = b->tail;

	atail->tail = bhead;
	bhead->head = atail; //set tail of A's tail to B's head, and vice versa

	a->tail = btail;	//set tail of list A to B's tail

	a->size = a->size + b->size;	//fix the size

	free(b);			//free up the LinkedList b space
}

//Search for a target with a provided compare function.
void* linked_list_search(LinkedList* list, void* target, int (*cmp)(const void*,const void*)) {
	LinkedListNode* cur_node = list->head;

	while (cur_node && cmp(cur_node->data, target)) {
		cur_node = cur_node->tail;
	}

	return cur_node->data;
}

//Remove an element from a list and return its data
void* linked_list_remove(LinkedList* list, int index) {
	if (index >= list->size) {
		return NULL; //element not found
	}
	LinkedListNode* cur_node;
	if (index < list->size/2) {
		//first half of the list, so iterate forwards
		cur_node = list->head;
		while (index > 0) {
			cur_node = cur_node->tail;
			index--;
		}
	} else {
		//more than halfway along, so iterate backwards
		cur_node = list->tail;
		index = list->size - 1 - index;	//transform the index into distance from tail
		while (index > 0) {
			cur_node = cur_node->head;
			index--;
		}
	}
	LinkedListNode* head = cur_node->head;
	LinkedListNode* tail = cur_node->tail;
	head->tail = tail;
	tail->head = head; //remove the node from the list by pointing the other nodes at each other
	void* data = cur_node->data;
	free(cur_node);		//free the node to prevent memory leaks
	list->size = list->size - 1;
	return data;
}

void linked_list_free(LinkedList* list) {
	if (list->size > 0) {	//if there are elements in the list
		LinkedListNode* cur_node = list->head;
		while (cur_node) {	//cur_node will be nul/0 if we've run out of elements
			LinkedListNode* next_node = cur_node->tail;
			free(cur_node);
			cur_node = next_node;
		}
	}
	free(list);
}

void linked_list_free_and_data(LinkedList* list) {
	if (list->size > 0) {	//if there are elements in the list
		LinkedListNode* cur_node = list->head;
		while (cur_node) {	//cur_node will be nul/0 if we've run out of elements
			LinkedListNode* next_node = cur_node->tail;
			free(cur_node->data);
			free(cur_node);
			cur_node = next_node;
		}
	}
	free(list);
}