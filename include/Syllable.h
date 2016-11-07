/**		@file		Syllable.h
*		@author		Tim Rollet
*		@date		11/6/2016
*		@brief		Provide ways to create and interact with Syllable spellwords.
*/

#ifndef SYLLABLE_H
#define SYLLABLE_H

#include "LinkedList.h"

#define SYLLABLE_MAX_NAME_LEN	12

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
	LinkedList* effects;
	DAMAGE_TYPE damage_type;
} Syllable;



Syllable* combine_syllables(LinkedList* syllables);				//TODO
void pick_targets(Syllable* word, char* enemy_pos); 			//TODO

Syllable* copy_syllable(Syllable* syl);
int roll_damage(Syllable* word);
void syllable_info(Syllable* syllable, char* buf, int size);
Syllable* search_for_syllable(LinkedList* list, char* name);

Syllable* syllable_create();
void syllable_destroy(Syllable* syl);

//Compares a syllable with a given syllable name (for use w/ linked_list_search)
int syllable_name_compare(const void* syllable, const void* name);
#endif
