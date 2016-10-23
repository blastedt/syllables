#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "LinkedList.h"

#define TEST_SIZE 1000
void lots_of_adds() {
	int* elements = malloc(sizeof(int) * TEST_SIZE);
	srand((unsigned int) time(NULL));
	LinkedList* list = linked_list_create();
	for (int i = 0; i < TEST_SIZE; i++) {
		elements[i] = rand();
		linked_list_add(list, (void*) elements[i]);
	}

	for (int j = 0; j < TEST_SIZE; j++) {
		int correct = elements[j];
		int test = (int) linked_list_get(list, j);
		if (correct != test) {
			printf("Lots of adds failed: retrieved element not correct");
			exit(1);
		}
	}

	linked_list_free(list);
}


int main() {
	lots_of_adds();
	printf("Lots of adds succeeded");
}