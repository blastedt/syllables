#include <time.h>
#include <stdlib.h>

#include "Model.h"
#include "Player.h"
#include "LinkedList.h"
#include "Syllable.h"
#include "stubs.h"
#include "util.h"

/**
*		@brief The singleton containing the only model info.
*		This should only be grabbed with get_model_singleton so model can enforce access.
*/
SyllableModel* model_singleton;
/** Constructs an empty model and returns a pointer to it. 
* Must be freed/destructed when done
* SETS THE SINGLETON
*/
SyllableModel* model_constructor() {
	if (model_singleton) return NULL;
	model_singleton = (SyllableModel*) malloc(sizeof(SyllableModel));
	model_singleton->player = NULL;
	model_singleton->effects = linked_list_create();
	model_singleton->enemies = malloc(sizeof(Enemy) * MAX_ENEMY_COUNT);
	model_singleton->score = 0;
	model_singleton->playing = STATE_NEED_NAME;

	return model_singleton;
}

/** Destructs and frees a model and its fields. 
*	If this is the singleton, remember to null the reference after.
*/
void model_destructor(SyllableModel* model) {
	//this is pretty much self explanatory, destroy all parts of the model
	destruct_player(model->player);
	if (model->effects) linked_list_free_and_data(model->effects, \
		(void(*)(void*))&destruct_effect);							//cast void destruct_effect (Effect*) function to void (*) (void*)
	if (model->enemies) free(model->enemies);
	free(model);
}

/** Destruct the singleton.
*
*/
void destruct_singleton() {
	model_destructor(model_singleton);
	model_singleton = NULL;
}

/** Get a reference to the model singleton.
*	Probably unsafe to call yourself - get a copy
*	If there is no model singleton, make an empty one.
**/
SyllableModel* get_model_singleton() {
	if (!model_singleton) return model_constructor();
	return model_singleton;
}

/** Initialize the model and start a game!
*	Also sets the seed.
*/
void new_game (char* name) {
	srand(time(NULL));
	model_singleton->player = construct_player(name);
	model_singleton->playing = STATE_PLAYING;
	model_singleton->score = 0;
}

/**	@brief	Pick the targets for a spellword.
*	@param	enemy_arr	current positions of all enemies
*	@return	an int array containing positions of targets to hit at 0...target_count (with extraneous elements after)
*	@note	Please free the returned value
*/
int* pick_syllable_targets(Enemy* enemy_arr) {
	int* target_choices = malloc(sizeof(int) * MAX_ENEMY_COUNT);
	int t_i = 0;
	for (int e_i = 0; e_i < MAX_ENEMY_COUNT; e_i++) {
		if (enemy_arr[e_i].alive) {
			target_choices[t_i] = e_i;
			t_i++;
		}
	}
	//after that t_i is the size of target_choices and target_choices 0...t_i is filled with enemy positions
	shuffle_int_array(target_choices, t_i);
	target_choices[t_i] = -1;	//watchdog value to end array
	return target_choices;		//shuffled array, now our targets are in the first word->target_count slots.
}

/**	@brief	Cast a spellword upon the battlefield, and allows enemies to retaliate.
*			This is the main function to update game state.
*			The player is only allowed to cast spells.  When they do, enemies get their turn.
*			This function will propagate effects, cast a spell, check enemy death, assign loot, cast enemy spells, 
*			and check player death.
*	@param	syllables	The spellword to cast
*/
void cast(LinkedList* syllables) {
	if (! model_singleton->state == STATE_PLAYING) {
		return;
	}
	/** @todo propagate effects */
	
	/** cast a spell */
	Syllable* spellword = combine_syllables(syllables);
	int* targets = pick_syllable_targets(model_singleton->enemies);

	for (int target_num = 0; target_num < spellword->target_count; target_num++) {
		/* for each target */
		Enemy* target = &model_singleton->enemies[target_num];
		int damage = roll_damage(spellword);
		int alive = damage_enemy(target, damage);
		if (!alive) {
			/** killed enemy effects */
			add_exp(model_singleton->player, target->xp);
		}
	}

	free(targets);

	int living_enemies = 0;
	int player_alive = 1;
	for (int e_i = 0; e_i < MAX_ENEMY_COUNT; e_i++) {
		Enemy* enemy = &model_singleton->enemies[e_i];
		if (!enemy->alive) continue;
		living_enemies++;
		/** Cast enemy spell */
		Syllable* word = enemy->spellword;
		if (word->target_count > 0) {		//enemies with ineffective words are out of luck
			int damage = roll_damage(word);
			player_alive = damage_player(model_singleton->player, damage);
			if (!player_alive) break;
		}
		/** @todo	Add enemy spelleffects. */
	}
	/** check for player death */
	if (!player_alive) {
		model_singleton->state = STATE_DEAD;
	}
}