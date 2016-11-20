/**
*			@file 	Model.h
*			@author Tim Rollet
*			@date 	11/6/2016
*			@brief	Stores and updates model for Syllables game.
*/

#ifndef SYLLABLES_MODEL_H
#define SYLLABLES_MODEL_H

#define USE_METHOD_STUBS_FOR_COMPILING             //REMOVE PRIOR TO RELEASE BUILDS, COMPILES METHOD STUBS IN TO PREVENT COMPILATION ERRORS FOR UNIMPL METHODS

#include "Enemy.h"
#include "Player.h"
#include "LinkedList.h"
#include "Syllable.h"
#include "stubs.h"


#define MAX_ENEMY_COUNT 6			/**< The maximum number of enemies on the battlefield at once */

/** @brief What state the game is in
*/
typedef enum {
	STATE_NEED_NAME,
	STATE_PLAYING,
	STATE_DEAD
} PLAY_STATE;

/** @brief Holds vital information about the Syllable game
*/
typedef struct Syllable_Model_S {
	Player* player;					/**< Pointer to the player singleton */
	LinkedList* effects;			/**< Active battlefield effects */
	Enemy* enemies;					/**< Active enemies.  MAX_ENEMY_COUNT size array */
	int score;						/**< How many points the player has earned in this game */
	PLAY_STATE playing;	
} SyllableModel;

/** @brief	Holds information about what kind of inventory is being accessed
*/
typedef enum {
	ARMOR,
	RING,
	WEAPON
} INVENTORY_TYPE;
/** @brief	Holds information about what kind of information is requested
*/
typedef enum {
	ARMOR_INFO,
	RING_INFO,
	WEAPON_INFO,
	SYLLABLE_INFO,
	EFFECTS_INFO
} INFO_TYPE;

SyllableModel* model_constructor();
void model_destructor(SyllableModel* model);
void destruct_singleton();


SyllableModel* get_model_singleton();		//INTERNAL ACCESS

//PUBLIC METHODS
void new_game (char* name);
void info (INFO_TYPE type, int selector, char* buf, int size);
void cast (LinkedList* syllables);
void equip (INVENTORY_TYPE type, int selector);

int* pick_syllable_targets(Syllable* word, Enemy* enemy_arr);

#endif