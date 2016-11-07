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

/** @brief Holds vital information about the Syllable game
*/
typedef struct Syllable_Model_S {
	Player* player;					/**< Pointer to the player singleton */
	LinkedList* effects;			/**< Active battlefield effects */
	Enemy* enemies;					/**< Active enemies.  MAX_ENEMY_COUNT size array */
	int score;						/**< How many points the player has earned in this game */
	PLAY_STATE playing;				/**< Is the game actively in progress (1), finished (-1), or not yet started (0)? */
} SyllableModel;

/** @brief What state the game is in
*/
typedef enum PLAY_STATE_E {
	NEED_NAME,
	PLAYING,
	DEAD
}	PLAY_STATE

/** @brief	Holds information about what kind of inventory is being accessed
*/
typedef enum INVENTORY_TYPE_E {
	ARMOR,
	RING,
	WEAPON
} INVENTORY_TYPE;
/** @brief	Holds information about what kind of information is requested
*/
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
void new_game (char* name);
void info (INFO_TYPE type, int selector, char* buf, int size);
void cast (LinkedList* syllables);
void equip (INVENTORY_TYPE type, int selector);

int* pick_syllable_targets(Syllable* word, Enemy* enemy_arr);

#endif