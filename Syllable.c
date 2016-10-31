#include "Syllable.h"
#include <stdlib.h>
#include <stdio.h>



Syllable* syllable_create() {
	Syllable* syl = (Syllable*) malloc(sizeof(Syllable));
}

void buff_free_stub(void* buff) {
	//do nothing
	//todo: need actual function to free buffs once theyre around
}

void syllable_destroy(Syllable* syl) {
	if (syl->name) free(syl->name);
	if (syl->buffs) {
		linked_list_free_and_data(syl->buffs, &buff_free_stub);
	}
	free(syl);
}

//Rolls for damage (min-max)*effectiveness
//Requires srand to have been called at some point to seed the generator.
int roll_damage(Syllable* word) {
	int damage_range = word->max_damage - word->min_damage;
	int damage = rand() % damage_range + word->min_damage;
	damage *= damage_effectiveness;

	return damage;
}

//Prints syllable info into provided buffer with given size
void syllable_info(Syllable* syllable, char* buf, int size) {
	//get the name and capitalize it
	char* name_copy = malloc(sizeof(char)*syllable->name_len+1);
	strncpy(name_copy, syllable->name, syllable->name_len);
	name_copy[0] = toupper(name_copy[0]);
	
	snprintf(buf, size, "\"%s!\"\nAdds (%d-%d) damage\nHits %d additional targets\nMultiplies total damage by %f%%", \
		name_copy, syllable->min_damage, syllable->max_damage, syllable->target_count, syllable->damage_effectiveness);
}

int syllable_name_compare(void* syllable, void* name) {
	return strcmp( ((Syllable*) syllable)->name, (char*) name);
}

Syllable* search_for_syllable(LinkedList* list, char* name) {
	return (Syllable*) linked_list_search(list, (void*) name, &syllable_name_compare);
}