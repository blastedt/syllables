#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdlib.h>

typedef struct LinkedList_s {
	struct LinkedList_s * head;
	struct LinkedList_s * tail;
	void* data;
	int size;
} LinkedList;

void* linked_list_get(LinkedList* list, int index);
void linked_list_add(LinkedList* list, void* data);
void linked_list_append(LinkedList* a, LinkedList* b);
void linked_list_destroy(LinkedList* list);
void* linked_list_remove(LinkedList* list, int index);


#endif