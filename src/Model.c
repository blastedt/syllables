#include "Model.h"
#include "Player.h"
#include "LinkedList.h"
#include "Syllable.h"
#include "stubs.h"


Syllable_Model* model_singleton;

Syllable_Model* model_constructor() {
	if (model_singleton) return NULL;
	model_singleton = (Syllable_Model*) malloc(sizeof(Syllable_Model));
	model_singleton->player = construct_player();
	model_singleton->effects = linked_list_create();
	model_singleton->enemies = malloc(sizeof(Enemy) * MAX_ENEMY_COUNT);
	model_singleton->score = 0;
	model_singleton->playing = 0;

	return model_singleton;
}

void model_destructor(Syllable_Model* model) {
	//this is pretty much self explanatory, destroy all parts of the model
	destruct_player(model->player);
	if (model->effects) linked_list_free_and_data(model->effects, \
		(void(*)(void*))&destruct_effect);							//cast void destruct_effect (Effect*) function to void (*) (void*)
	//TODO: Rest of destructor
}
