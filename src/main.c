#include "Enemy.h"
#include "Player.h"
#include "LinkedList.h"
#include "Syllable.h"

//////////////////////////////////////////////plz note im not using this file anymore

#include "stubs.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define INFO_STRING_SIZE 150

void prompt_for_name(char* result, int length) {
	do {
		printf("What is your name, magus? \n");
		fgets(result, length, stdin);
		int len = strlen(result);
		if (result[len-1] == '\n') result[--len] = 0;
		if (!(len <= 0 || len > 9)) return;
	} while (1);
}


void info (char** tokens) {0
	//Todo: refactor into dictionary of some sort
	char* infostring = malloc(sizeof(char) * INFO_STRING_SIZE);
	if (!strcmp(tokens, "armor")) {
		info_armor(&tokens[1], infostring, INFO_STRING_SIZE);		//armor info with rest of tokens
	} else if (!strcmp(tokens, "effects")) {
		info_effects(&tokens[1], infostring, INFO_STRING_SIZE);
	} else if (!strcmp(tokens, "staff") || !strcmp(tokens, "weapon")) {
		info_weapon(&tokens[1], infostring, INFO_STRING_SIZE);
	} else {
		info_syllable
	}
}


int main(int argc, char** argv) {
	char* name = malloc(sizeof(char) * 13);
	prompt_for_name(name, 12);
	printf("%s", name);
	free(name);
	return 0;
}