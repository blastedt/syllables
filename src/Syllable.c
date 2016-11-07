#include "Syllable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stubs.h"
/** Creates an empty syllable. 
*/
Syllable* syllable_create() {
	Syllable* syl = (Syllable*) malloc(sizeof(Syllable));
	syl->effects = NULL;			//Effects are not in Milestone 1
	//syl->effects = linked_list_create();
	return syl;
}
/** Destructs a syllable and fields. 
*/
void syllable_destroy(Syllable* syl) {
	if (syl->name) free(syl->name);
	//if (syl->effects) {
	//	linked_list_free_and_data(syl->effects, (void(*)(void*)) &destruct_effect);
	//}
	free(syl);
}
/** Gets the raw damage of this syllable or spellword. 
* Rolls for damage (min-max)*effectiveness
* Requires srand to have been called at some point to seed the generator.
*/
int roll_damage(Syllable* word) {
	int damage_range = word->max_damage - word->min_damage;
	int damage = rand() % damage_range + word->min_damage;
	damage *= word->damage_effectiveness;

	return damage;
}

/** Prints syllable info into provided buffer with given size. 
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

/** Compares a syllable's name with a string. 
* For use with linked_list_search
*/
int syllable_name_compare(const void* syllable, const void* name) {
	return strcmp( ((Syllable*) syllable)->name, (char*) name);
}
/** Search a list of syllables by name. 
*/
Syllable* search_for_syllable(LinkedList* list, char* name) {
	return (Syllable*) linked_list_search(list, (void*) name, &syllable_name_compare);
}


/** @brief	Deep copy a syllable and return a pointer to the new one.
*			Must be freed when done using.
*	@todo	Copy effects
*/
Syllable* copy_syllable(Syllable* syllable) {
	Syllable* copy = (Syllable*) malloc(sizeof(Syllable));
	copy->min_damage = syllable->min_damage;
	copy->max_damage = syllable->max_damage;
	copy->damage_effectiveness = syllable->damage_effectiveness;
	copy->target_count = syllable->target_count;
	copy->name = (char*) malloc(syllable->name_len + 1);
	strncpy(copy->name, syllable->name, syllable->name_len);
	copy->name_len = syllable->name_len;
	//copy->effects = linked_list_copy(syllable->effects, effect_copy);
	copy->damage_type = syllable->damage_type;
}

/** @brief	Combine a list of syllables into a single spellword.
*			The combined spellword is ready to be casted.
*			The spellword should be freed after use.
*	@todo	Potential improvement by iterating only once along list (O(n)) instead of n times (O(n^2)).
*			Perhaps implement a foldr() function into linked_list? Then put contents of for-loop into a lambda for it.
*	@todo	Effects
*/
Syllable* combine_syllables(LinkedList* syllables) {
	Syllable* word = copy_syllable((Syllable*) syllables->head->data);
	char* final_name = malloc(sizeof(char)*SYLLABLE_MAX_NAME_LEN*syllables->size);
	strcat(final_name, word->name);
	free(word->name);
	word->name = final_name;
	for (int syl_index = 1; syl_index < syllables->size; syl_index++) {
		Syllable* syl = (Syllable*) linked_list_get(syllables, syl_index);
		word->min_damage += syl->min_damage;
		word->max_damage += syl->max_damage;
		word->damage_effectiveness *= syl->damage_effectiveness;
		word->target_count += syl->target_count;
		strcat(final_name, " ");
		strcat(final_name, syl->name);
		//linked_list_append(word->effects, syl->effects);
		/** @todo Damage type addition (milestone 3) */
	}
	strcat(final_name, "!");
	return word;
}