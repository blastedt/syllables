#ifndef SYLLABLE_H
#define SYLLABLE_H

#include "LinkedList.h"

typedef enum DAMAGE_TYPE_E {
	NONE,
	FIRE,
	ACID,
	SHADOW
} DAMAGE_TYPE;

typedef struct {
	int min_damage;
	int max_damage;
	float damage_effectiveness;
	int target_count;
	char* name;
	int name_len;
	LinkedList* buffs;
	DAMAGE_TYPE damage_type;
} Syllable;



Syllable* combine_syllables(LinkedList* syllables);


char pick_targets(Syllable* word, char enemies); //use char as bitfield
int roll_damage(Syllable* word);
char* syllable_info(Syllable* syllable);
Syllable* search_for_syllable(LinkedList* list, char* name);
#endif