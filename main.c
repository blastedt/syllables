#include "Enemy.h"
#include "Player.h"
#include "LinkedList.h"
#include "Syllable.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void prompt_for_name(char* result, int length) {
	do {
		printf("What is your name, magus? \n");
		fgets(result, length, stdin);
		int len = strlen(result);
		if (result[len-1] == '\n') result[--len] = 0;
		if (!(len <= 0 || len > 9)) return;
	} while (1);
}


int main(int argc, char** argv) {
	char* name = malloc(sizeof(char) * 13);
	prompt_for_name(name, 12);
	printf("%s", name);
	free(name);
	return 0;
}