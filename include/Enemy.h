/**		@file		Enemy.h
*		@author		Tim Rollet
*		@date		11/6/2016
*		@brief		Provide methods to interact with Enemies in Syllable game.
*		@todo		Everything
*/

#ifndef ENEMY_H
#define ENEMY_H


#include "Player.h"
#include "LinkedList.h"
#include "Syllable.h"

typedef struct Enemy_s {
	Syllable* spellword;
	int hp;
	int max_hp;
	int damage_reduction;
	LinkedList* loot;
	int	alive;
} Enemy;

#endif