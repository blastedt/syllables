#include "Syllable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stubs.h"
/*! Creates an empty syllable. 
*/
Syllable* syllable_create() {
	Syllable* syl = (Syllable*) malloc(sizeof(Syllable));
	syl->effects = linked_list_create();
	return syl;
}
/*! Destructs a syllable and fields. 
*/
void syllable_destroy(Syllable* syl) {
	if (syl->name) free(syl->name);
	if (syl->effects) {
		linked_list_free_and_data(syl->effects, &destruct_effect_void);
	}
	free(syl);
}
/*! Gets the raw damage of this syllable or spellword. 
* Rolls for damage (min-max)*effectiveness
* Requires srand to have been called at some point to seed the generator.
*/
int roll_damage(Syllable* word) {
	int damage_range = word->max_damage - word->min_damage;
	int damage = rand() % damage_range + word->min_damage;
	damage *= word->damage_effectiveness;

	return damage;
}

/*! Prints syllable info into provided buffer with given size. 
* Hopefully is safe, but who will try to buffer overflow this anyways?
*/
void syllable_info(Syllable* syllable, char* buf, int size) {
	//get the name and capitalize it
	char* name_copy = malloc(sizeof(char)*syllable->name_len+1);
	strncpy(name_copy, syllable->name, syllable->name_len);
	name_copy[0] = toupper(name_copy[0]);
	
	snprintf(buf, size, "\"%s!\"\nAdds (%d-%d) damage\nHits %d additional targets\nMultiplies total damage by %f%%", \
		name_copy, syllable->min_damage, syllable->max_damage, syllable->target_count, syllable->damage_effectiveness);
}

/*! Compares a syllable's name with a string. 
* For use with linked_list_search
*/
int syllable_name_compare(const void* syllable, const void* name) {
	return strcmp( ((Syllable*) syllable)->name, (char*) name);
}
/*! Search a list of syllables by name. 
*/
Syllable* search_for_syllable(LinkedList* list, char* name) {
	return (Syllable*) linked_list_search(list, (void*) name, &syllable_name_compare);
}
