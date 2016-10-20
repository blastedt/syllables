#include <string.h>
#include <stdio.h>

#include "LinkedList.h"
#include "Syllable.h"
void* linked_list_get(LinkedList* list, int index) {
	if (list == NULL || index < 0) return 0;		//index out of range
	if (index == 0) return (*list).data;
	return linked_list_get((*list).tail, index-1);
}

void linked_list_add(LinkedList* list, void* data) {
	if ((*list).tail == NULL) {
		LinkedList* new_element = (LinkedList*) malloc(sizeof(LinkedList));
		(*list).tail = new_element;
		(*new_element).head = list;
	} else {
		linked_list_add((*list).tail, data);
	}
}

LinkedList* linked_list_new(void* data) {
	LinkedList* list = malloc(sizeof(LinkedList));
	(*list).head = NULL;
	(*list).tail = NULL;
	list->data = data;
	return list;
}

void linked_list_append(LinkedList* a, LinkedList* b) {
	if ((*a).tail == NULL) {
		(*a).tail = b;
		(*b).head = a;
	} else {
		linked_list_append((*a).tail, b);
	}
}

void linked_list_destroy(LinkedList* list) {
	if ((*list).tail != NULL) {
		linked_list_destroy((LinkedList*)(*list).tail);
	}
	free(list);
}

void* linked_list_remove(LinkedList* list, int index) {		//will orphan reference if you free the first element. so. don't do that. yeah.
	if (list == NULL || index < 0) return 0;		//index out of range
	if (index == 0){
		LinkedList* head = (*list).head;
		LinkedList* tail = (*list).tail;
		free(list);
		if (head == NULL) {
			printf("Fatal error: orphaned linked list elements (did you remove element zero?)");
			exit(1);
		}
		if (tail != NULL) {
			//didn't remove last element
			(*head).tail = tail;
			(*tail).head = head;
		} else {
			(*head).tail = NULL;
		}

		return (*list).data;
	} 
	return linked_list_remove((*list).tail, index-1);
}

Syllable* search_for_syllable(LinkedList* list, char* name) {
	if (list == NULL) return NULL;
	if (!strcmp(name, ((Syllable*) (list->data))->name)) return (Syllable*) list->data;
	return search_for_syllable(list->tail, name);
}