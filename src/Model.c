#include "Model.h"
#include "Player.h"
#include "LinkedList.h"
#include "Syllable.h"
#include "stubs.h"

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
	model_singleton->player = construct_player();
	model_singleton->effects = linked_list_create();
	model_singleton->enemies = malloc(sizeof(Enemy) * MAX_ENEMY_COUNT);
	model_singleton->score = 0;
	model_singleton->playing = PLAY_STATE.NEED_NAME;

	return model_singleton;
}

/** Destructs and frees a model and its fields. 
If this is the singleton, remember to null the reference after.
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
*	
*/
void new_game (char* name) {
	model->player = new_player(name);
	model->playing = PLAY_STATE.PLAYING;
	model->score = 0;
}