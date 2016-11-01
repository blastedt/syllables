#ifndef SYLLABLES_MODEL_H
#define SYLLABLES_MODEL_H

#define USE_METHOD_STUBS_FOR_COMPILING             //REMOVE PRIOR TO RELEASE BUILDS, COMPILES METHOD STUBS IN TO PREVENT COMPILATION ERRORS FOR UNIMPL METHODS

#include "Enemy.h"
#include "Player.h"
#include "LinkedList.h"
#include "Syllable.h"
#include "stubs.h"


#define MAX_ENEMY_COUNT 6

typedef struct Syllable_Model_S {
	Player* player;
	LinkedList* effects;
	Enemy* enemies;
	int score;
	int playing;
} Syllable_Model;

typedef enum INVENTORY_TYPE_E {
	ARMOR,
	RING,
	WEAPON
} INVENTORY_TYPE;

typedef enum INFO_TYPE_E {
	ARMOR_INFO,
	RING_INFO,
	WEAPON_INFO,
	SYLLABLE_INFO,
	EFFECTS_INFO
} INFO_TYPE;

Syllable_Model* model_constructor();
void model_destructor(Syllable_Model* model);
void destruct_singleton();


Syllable_Model* get_model_singleton();		//INTERNAL ACCESS

//PUBLIC METHODS
void init_model (char* name);
void info (INFO_TYPE type, int selector, char* buf, int size);
void cast (LinkedList* syllables);
void equip (INVENTORY_TYPE type, int selector);
Syllable_Model* get_model_copy();			//USE THIS METHOD FOR EXTERNAL ACCESS, RETURNS COPY (PLZ FREE)

#endif